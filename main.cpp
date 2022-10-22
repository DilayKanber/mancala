#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string>

#define PI 3.14

int selected=0;
int player=1;
int game = 1;

struct holes{
    int stone_num=0;
    float center_point_x,center_point_y;
    float text_x,text_y;
}A[7],B[7];

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius);
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);
void mancala();
void reshape(int ,int );
void draw_game_board();
void draw_text();
void setValues();
int carry_stones();
void win_check();
void draw_over();

int main(int argc, char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    setValues();

    glutInitWindowPosition(300,0);
    glutInitWindowSize(800,800);
    glutCreateWindow("Mancala games");
    glutDisplayFunc(mancala);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
void mancala(){
    glClearColor(0.2,0.1,0.2,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw_game_board();
    draw_text();

    if(game==1){
        glutKeyboardFunc(processNormalKeys);
        glutSpecialFunc(processSpecialKeys);

        carry_stones();
        win_check();
    }
    else{
        draw_over();
    }
    glutPostRedisplay();

    glutSwapBuffers();
}
void reshape(int w,int h){
    glViewport(0,0,800,800);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20,20,-20,20);
    glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys(unsigned char key, int x, int y){
    if(player==1)
    {
        if (key=='1'){
            selected=1;
            player+=1;
        }
        else if(key=='2'){
            selected=2;
            player+=1;
        }
        else if(key=='3'){
            selected=3;
            player+=1;
        }
        else if(key=='4'){
            selected=4;
            player+=1;
        }
        else if(key=='5'){
            selected=5;
            player+=1;
        }
        else if(key=='6'){
            selected=6;
            player+=1;
        }

    }
}
void processSpecialKeys(int key, int x, int y) {

    if(player==2)
    {
        switch(key) {
            case GLUT_KEY_F1 :
                selected=12; player-=1; break;
            case GLUT_KEY_F2 :
                selected=11; player-=1; break;
            case GLUT_KEY_F3 :
                selected=10; player-=1; break;
            case GLUT_KEY_F4 :
                selected=9; player-=1; break;
            case GLUT_KEY_F5 :
                selected=8; player-=1; break;
            case GLUT_KEY_F6 :
                selected=7; player-=1; break;
        }

    }
}

void win_check(){
    int flag1=1,flag2=1;
    for(int i=0;i<6;i++){
        if(A[i].stone_num!=0)
            flag1=0;
    }
    for(int i=0;i<6;i++){
        if(B[i].stone_num!=0)
            flag2=0;
    }
    if(flag1==1){
        for(int i=0;i<6;i++){
            A[6].stone_num+=B[i].stone_num;
            B[i].stone_num = 0;
        }
        game=0;
    }
    if(flag2==1){
        for(int i=0;i<6;i++){
            B[6].stone_num+=A[i].stone_num;
            A[i].stone_num = 0;
        }
        game=0;
    }
}
void draw_over(){

    if(A[6].stone_num>B[6].stone_num){

        unsigned char string[]="W I N N E R  ->  PLAYER 1 !";
        glRasterPos2f(-8,16);

        int len = strlen((const char*)string);
        for (int j = 0; j < len; j++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[j]);
        }
    }
    else if(A[6].stone_num<B[6].stone_num){

        unsigned char string[]="W I N N E R  ->  PLAYER 2 !";
        glRasterPos2f(-8,16);

        int len = strlen((const char*)string);
        for (int j = 0; j < len; j++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[j]);
        }
    }
    else{
        unsigned char string[]="N O   W I N N E R !";
        glRasterPos2f(-5,16);

        int len = strlen((const char*)string);
        for (int j = 0; j < len; j++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[j]);
        }
    }



}

int carry_stones(){
    int carry;
    int i;
    switch(selected) {
		case 1 :
		    carry = A[0].stone_num;
		    A[0].stone_num = 0;
		    if(carry == 0){
                player-=1;
                selected = 0 ;
                return 0;
		    }
		    else if(carry == 1){
                A[0].stone_num=0;
                if(A[1].stone_num==0){
                    A[6].stone_num+=B[4].stone_num;
                    B[4].stone_num=0;
                    A[6].stone_num++;
                }
                else
                    A[1].stone_num+=1;
		    }
		    else if(carry < 8){
		        for(i=0;i<carry;i++){
                    A[i].stone_num+=1;
		        }
		        if (i==7)
                    player-=1;
                if(A[i-1].stone_num == 1 && i != 7){
                    A[6].stone_num += B[5-(i-1)].stone_num;
                    B[5-(i-1)].stone_num = 0;
                    A[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 15){
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-7;i++){
                    B[i].stone_num+=1;
		        }
		        if(B[i-1].stone_num%2==0 && i!=7){
		            A[6].stone_num+=B[i-1].stone_num;
                    B[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 22){
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-14;i++){
                    A[i].stone_num+=1;
		        }
		        if (i==7)
                    player-=1;
                if(A[i-1].stone_num == 1 && i != 7){
                    A[6].stone_num += B[5-(i-1)].stone_num;
                    B[5-(i-1)].stone_num = 0;
                    A[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else{
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-21;i++){
                    B[i].stone_num+=1;
		        }
		        if(B[i-1].stone_num%2==0 && i!=7){
		            A[6].stone_num+=B[i-1].stone_num;
                    B[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    break;
		case 2 :
		    carry = A[1].stone_num;
		    A[1].stone_num = 0;
		    if(carry == 0){
		        player-=1;
                selected = 0 ;
                return 0;
		    }
		    else if(carry == 1){
                A[1].stone_num=0;
                if(A[2].stone_num==0){
                    A[6].stone_num+=B[3].stone_num;
                    B[3].stone_num=0;
                    A[6].stone_num++;
                }
                else
                    A[2].stone_num+=1;
		    }
		    else if(carry < 7){
		        for(i=1;i<carry+1;i++){
                    A[i].stone_num+=1;
		        }
		        if (i==7)
                    player-=1;
                if(A[i-1].stone_num == 1 && i != 7){
                    A[6].stone_num += B[5-(i-1)].stone_num;
                    B[5-(i-1)].stone_num = 0;
                    A[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 14){
		        for(i=1;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-6;i++){
                    B[i].stone_num+=1;
		        }
		        if(B[i-1].stone_num%2==0 && i!=7){
		            A[6].stone_num+=B[i-1].stone_num;
                    B[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 21){
		        for(i=1;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-13;i++){
                    A[i].stone_num+=1;
		        }
		        if (i==7)
                    player-=1;
                if(A[i-1].stone_num == 1 && i != 7){
                    A[6].stone_num += B[5-(i-1)].stone_num;
                    B[5-(i-1)].stone_num = 0;
                    A[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else{
		        for(i=1;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-20;i++){
                    B[i].stone_num+=1;
		        }
		        if(B[i-1].stone_num%2==0 && i!=7){
		            A[6].stone_num+=B[i-1].stone_num;
                    B[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    break;
		case 3 :
		    carry = A[2].stone_num;
		    A[2].stone_num = 0;
		    if(carry == 0){
                player-=1;
                selected = 0 ;
                return 0;
		    }
		    else if(carry == 1){
                A[2].stone_num=0;
                if(A[3].stone_num==0){
                    A[6].stone_num+=B[2].stone_num;
                    B[2].stone_num=0;
                    A[6].stone_num++;
                }
                else
                    A[3].stone_num+=1;
		    }
		    else if(carry < 6){
		        for(i=2;i<carry+2;i++){
                    A[i].stone_num+=1;
		        }
		        if (i==7)
                    player-=1;
                if(A[i-1].stone_num == 1 && i != 7){
                    A[6].stone_num += B[5-(i-1)].stone_num;
                    B[5-(i-1)].stone_num = 0;
                    A[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 13){
		        for(i=2;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-5;i++){
                    B[i].stone_num+=1;
		        }
		        if(B[i-1].stone_num%2==0 && i!=7){
		            A[6].stone_num+=B[i-1].stone_num;
                    B[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 20){
		        for(i=2;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-12;i++){
                    A[i].stone_num+=1;
		        }
		        if (i==7)
                    player-=1;
                if(A[i-1].stone_num == 1 && i != 7){
                    A[6].stone_num += B[5-(i-1)].stone_num;
                    B[5-(i-1)].stone_num = 0;
                    A[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else{
		        for(i=2;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-19;i++){
                    B[i].stone_num+=1;
		        }
		        if(B[i-1].stone_num%2==0 && i!=7){
		            A[6].stone_num+=B[i-1].stone_num;
                    B[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    break;
        case 4 :
            carry = A[3].stone_num;
		    A[3].stone_num = 0;
		    if(carry == 0){
                player-=1;
                selected = 0 ;
                return 0;
		    }
		    else if(carry == 1){
                A[3].stone_num=0;
                if(A[4].stone_num==0){
                    A[6].stone_num+=B[1].stone_num;
                    B[1].stone_num=0;
                    A[6].stone_num++;
                }
                else
                    A[4].stone_num+=1;
		    }
		    else if(carry < 5){
		        for(i=3;i<carry+3;i++){
                    A[i].stone_num+=1;
		        }
		        if (i==7)
                    player-=1;
                if(A[i-1].stone_num == 1 && i != 7){
                    A[6].stone_num += B[5-(i-1)].stone_num;
                    B[5-(i-1)].stone_num = 0;
                    A[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 12){
		        for(i=3;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-4;i++){
                    B[i].stone_num+=1;
		        }
		        if(B[i-1].stone_num%2==0 && i!=7){
		            A[6].stone_num+=B[i-1].stone_num;
                    B[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 19){
		        for(i=3;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-11;i++){
                    A[i].stone_num+=1;
		        }
		        if (i==7)
                    player-=1;
                if(A[i-1].stone_num == 1 && i != 7){
                    A[6].stone_num += B[5-(i-1)].stone_num;
                    B[5-(i-1)].stone_num = 0;
                    A[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else{
		        for(i=3;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-18;i++){
                    B[i].stone_num+=1;
		        }
		        if(B[i-1].stone_num%2==0 && i!=7){
		            A[6].stone_num+=B[i-1].stone_num;
                    B[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    break;
		case 5 :
		    carry = A[4].stone_num;
		    A[4].stone_num = 0;
		    if(carry == 0){
                player-=1;
                selected = 0 ;
                return 0;
		    }
		    else if(carry == 1){
                A[4].stone_num=0;
                if(A[5].stone_num==0){
                    A[6].stone_num+=B[0].stone_num;
                    B[0].stone_num=0;
                    A[6].stone_num++;
                }
                else
                    A[5].stone_num+=1;
		    }
		    else if(carry < 4){
		        for(i=4;i<carry+4;i++){
                    A[i].stone_num+=1;
		        }
		        if (i==7)
                    player-=1;
                if(A[i-1].stone_num == 1 && i != 7){
                    A[6].stone_num += B[5-(i-1)].stone_num;
                    B[5-(i-1)].stone_num = 0;
                    A[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 11){
		        for(i=4;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-3;i++){
                    B[i].stone_num+=1;
		        }
		        if(B[i-1].stone_num%2==0 && i!=7){
		            A[6].stone_num+=B[i-1].stone_num;
                    B[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 18){
		        for(i=4;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-10;i++){
                    A[i].stone_num+=1;
		        }
		        if (i==7)
                    player-=1;
                if(A[i-1].stone_num == 1 && i != 7){
                    A[6].stone_num += B[5-(i-1)].stone_num;
                    B[5-(i-1)].stone_num = 0;
                    A[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else{
		        for(i=4;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-17;i++){
                    B[i].stone_num+=1;
		        }
		        if(B[i-1].stone_num%2==0 && i!=7){
		            A[6].stone_num+=B[i-1].stone_num;
                    B[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    break;
		case 6 :
		    carry = A[5].stone_num;
		    A[5].stone_num = 0;
		    if(carry == 0){
                player-=1;
                selected = 0 ;
                return 0;
		    }
		    else if(carry == 1){
                A[5].stone_num=0;
                A[6].stone_num+=1;
                player-=1;
		    }
		    else if(carry < 3){
		        for(i=5;i<carry+5;i++){
                    A[i].stone_num+=1;
		        }
		        if (i==7)
                    player-=1;
                if(A[i-1].stone_num == 1 && i != 7){
                    A[6].stone_num += B[5-(i-1)].stone_num;
                    B[5-(i-1)].stone_num = 0;
                    A[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 10){
		        for(i=5;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-2;i++){
                    B[i].stone_num+=1;
		        }
		        if(B[i-1].stone_num%2==0 && i!=7){
		            A[6].stone_num+=B[i-1].stone_num;
                    B[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 17){
		        for(i=5;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-9;i++){
                    A[i].stone_num+=1;
		        }
		        if (i==7)
                    player-=1;
                if(A[i-1].stone_num == 1 && i != 7){
                    A[6].stone_num += B[5-(i-1)].stone_num;
                    B[5-(i-1)].stone_num = 0;
                    A[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 24){
		        for(i=5;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-16;i++){
                    B[i].stone_num+=1;
		        }
		        if(B[i-1].stone_num%2==0 && i!=7){
		            A[6].stone_num+=B[i-1].stone_num;
                    B[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    else{
		        for(i=5;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-23;i++){
                    A[i].stone_num+=1;
		        }
		        if (i==7)
                    player-=1;
                if(A[i-1].stone_num == 1 && i != 7){
                    A[6].stone_num += B[5-(i-1)].stone_num;
                    B[5-(i-1)].stone_num = 0;
                    A[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    break;
        case 7 :
		    carry = B[0].stone_num;
		    B[0].stone_num = 0;
		    if(carry == 0){
                player+=1;
                selected = 0 ;
                return 0;
		    }
		    else if(carry == 1){
                B[0].stone_num=0;
                if(B[1].stone_num==0){
                    B[6].stone_num+=A[4].stone_num;
                    A[4].stone_num=0;
                    B[6].stone_num++;
                }
                else
                    B[1].stone_num+=1;
		    }
		    else if(carry < 8){
		        for(i=0;i<carry;i++){
                    B[i].stone_num+=1;
		        }
		        if (i==7)
                    player+=1;
                if(B[i-1].stone_num == 1 && i != 7){
                    B[6].stone_num += A[5-(i-1)].stone_num;
                    A[5-(i-1)].stone_num = 0;
                    B[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 15){
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-7;i++){
                    A[i].stone_num+=1;
		        }
		        if(A[i-1].stone_num%2==0 && i!=7){
		            B[6].stone_num+=A[i-1].stone_num;
                    A[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 22){
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-14;i++){
                    B[i].stone_num+=1;
		        }
		        if (i==7)
                    player+=1;
                if(B[i-1].stone_num == 1 && i != 7){
                    B[6].stone_num += A[5-(i-1)].stone_num;
                    A[5-(i-1)].stone_num = 0;
                    B[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else{
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-21;i++){
                    A[i].stone_num+=1;
		        }
		        if(A[i-1].stone_num%2==0 && i!=7){
		            B[6].stone_num+=A[i-1].stone_num;
                    A[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    break;
		case 8 :
		    carry = B[1].stone_num;
		    B[1].stone_num = 0;
		    if(carry == 0){
                player+=1;
                selected = 0 ;
                return 0;
		    }
		    else if(carry == 1){
                B[1].stone_num=0;
                if(B[2].stone_num==0){
                    B[6].stone_num+=A[3].stone_num;
                    A[3].stone_num=0;
                    B[6].stone_num++;
                }
                else
                    B[2].stone_num+=1;
		    }
		    else if(carry < 7){
		        for(i=1;i<carry+1;i++){
                    B[i].stone_num+=1;
		        }
		        if (i==7)
                    player+=1;
                if(B[i-1].stone_num == 1 && i != 7){
                    B[6].stone_num += A[5-(i-1)].stone_num;
                    A[5-(i-1)].stone_num = 0;
                    B[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 14){
		        for(i=1;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-6;i++){
                    A[i].stone_num+=1;
		        }
		        if(A[i-1].stone_num%2==0 && i!=7){
		            B[6].stone_num+=A[i-1].stone_num;
                    A[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 21){
		        for(i=1;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-13;i++){
                    B[i].stone_num+=1;
		        }
		        if (i==7)
                    player+=1;
                if(B[i-1].stone_num == 1 && i != 7){
                    B[6].stone_num += A[5-(i-1)].stone_num;
                    A[5-(i-1)].stone_num = 0;
                    B[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else{
		        for(i=1;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-20;i++){
                    A[i].stone_num+=1;
		        }
		        if(A[i-1].stone_num%2==0 && i!=7){
		            B[6].stone_num+=A[i-1].stone_num;
                    A[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    break;
		case 9 :
		    carry = B[2].stone_num;
		    B[2].stone_num = 0;
		    if(carry == 0){
		        player+=1;
                selected = 0 ;
                return 0;
		    }
		    else if(carry == 1){
                B[2].stone_num=0;
                if(B[3].stone_num==0){
                    B[6].stone_num+=A[2].stone_num;
                    A[2].stone_num=0;
                    B[6].stone_num++;
                }
                else
                    B[3].stone_num+=1;
		    }
		    else if(carry < 6){
		        for(i=2;i<carry+2;i++){
                    B[i].stone_num+=1;
		        }
		        if (i==7)
                    player+=1;
                if(B[i-1].stone_num == 1 && i != 7){
                    B[6].stone_num += A[5-(i-1)].stone_num;
                    A[5-(i-1)].stone_num = 0;
                    B[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 13){
		        for(i=2;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-5;i++){
                    A[i].stone_num+=1;
		        }
		        if(A[i-1].stone_num%2==0 && i!=7){
		            B[6].stone_num+=A[i-1].stone_num;
                    A[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 20){
		        for(i=2;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-12;i++){
                    B[i].stone_num+=1;
		        }
		        if (i==7)
                    player+=1;
                if(B[i-1].stone_num == 1 && i != 7){
                    B[6].stone_num += A[5-(i-1)].stone_num;
                    A[5-(i-1)].stone_num = 0;
                    B[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else{
		        for(i=2;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-19;i++){
                    A[i].stone_num+=1;
		        }
		        if(A[i-1].stone_num%2==0 && i!=7){
		            B[6].stone_num+=A[i-1].stone_num;
                    A[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    break;
        case 10 :
            carry = B[3].stone_num;
		    B[3].stone_num = 0;
		    if(carry == 0){
                player+=1;
                selected = 0 ;
                return 0;
		    }
		    else if(carry == 1){
                B[3].stone_num=0;
                if(B[4].stone_num==0){
                    B[6].stone_num+=A[1].stone_num;
                    A[1].stone_num=0;
                    B[6].stone_num++;
                }
                else
                    B[4].stone_num+=1;
		    }
		    else if(carry < 5){
		        for(i=3;i<carry+3;i++){
                    B[i].stone_num+=1;
		        }
		        if (i==7)
                    player+=1;
                if(B[i-1].stone_num == 1 && i != 7){
                    B[6].stone_num += A[5-(i-1)].stone_num;
                    A[5-(i-1)].stone_num = 0;
                    B[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 12){
		        for(i=3;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-4;i++){
                    A[i].stone_num+=1;
		        }
		        if(A[i-1].stone_num%2==0 && i!=7){
		            B[6].stone_num+=A[i-1].stone_num;
                    A[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 19){
		        for(i=3;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-11;i++){
                    B[i].stone_num+=1;
		        }
		        if (i==7)
                    player+=1;
                if(B[i-1].stone_num == 1 && i != 7){
                    B[6].stone_num += A[5-(i-1)].stone_num;
                    A[5-(i-1)].stone_num = 0;
                    B[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else{
		        for(i=3;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-18;i++){
                    A[i].stone_num+=1;
		        }
		        if(A[i-1].stone_num%2==0 && i!=7){
		            B[6].stone_num+=A[i-1].stone_num;
                    A[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    break;
		case 11 :
		    carry = B[4].stone_num;
		    B[4].stone_num = 0;
		    if(carry == 0){
                player+=1;
                selected = 0 ;
                return 0;
		    }
		    else if(carry == 1){
                B[4].stone_num=0;
                if(B[5].stone_num==0){
                    B[6].stone_num+=A[0].stone_num;
                    A[0].stone_num=0;
                    B[6].stone_num++;
                }
                else
                    B[5].stone_num+=1;
		    }
		    else if(carry < 4){
		        for(i=4;i<carry+4;i++){
                    B[i].stone_num+=1;
		        }
		        if (i==7)
                    player+=1;
                if(B[i-1].stone_num == 1 && i != 7){
                    B[6].stone_num += A[5-(i-1)].stone_num;
                    A[5-(i-1)].stone_num = 0;
                    B[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 11){
		        for(i=4;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-3;i++){
                    A[i].stone_num+=1;
		        }
		        if(A[i-1].stone_num%2==0 && i!=7){
		            B[6].stone_num+=A[i-1].stone_num;
                    A[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 18){
		        for(i=4;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-10;i++){
                    B[i].stone_num+=1;
		        }
		        if (i==7)
                    player+=1;
                if(B[i-1].stone_num == 1 && i != 7){
                    B[6].stone_num += A[5-(i-1)].stone_num;
                    A[5-(i-1)].stone_num = 0;
                    B[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else{
		        for(i=4;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-17;i++){
                    A[i].stone_num+=1;
		        }
		        if(A[i-1].stone_num%2==0 && i!=7){
		            B[6].stone_num+=A[i-1].stone_num;
                    A[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    break;
		case 12 :
		    carry = B[5].stone_num;
		    B[5].stone_num = 0;
		    if(carry == 0){
                player+=1;
                selected = 0 ;
                return 0;
		    }
		    else if(carry == 1){
                B[5].stone_num=0;
                B[6].stone_num+=1;
                player+=1;
		    }
		    else if(carry < 3){
		        for(i=5;i<carry+5;i++){
                    B[i].stone_num+=1;
		        }
		        if (i==7)
                    player+=1;
                if(B[i-1].stone_num == 1 && i != 7){
                    B[6].stone_num += A[5-(i-1)].stone_num;
                    A[5-(i-1)].stone_num = 0;
                    B[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 10){
		        for(i=5;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-2;i++){
                    A[i].stone_num+=1;
		        }
		        if(A[i-1].stone_num%2==0 && i!=7){
		            B[6].stone_num+=A[i-1].stone_num;
                    A[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 17){
		        for(i=5;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-9;i++){
                    B[i].stone_num+=1;
		        }
		        if (i==7)
                    player+=1;
                if(B[i-1].stone_num == 1 && i != 7){
                    B[6].stone_num += A[5-(i-1)].stone_num;
                    A[5-(i-1)].stone_num = 0;
                    B[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    else if(carry < 24){
		        for(i=5;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<carry-16;i++){
                    A[i].stone_num+=1;
		        }
		        if(A[i-1].stone_num%2==0 && i!=7){
		            B[6].stone_num+=A[i-1].stone_num;
                    A[i-1].stone_num = 0;
		        }
		        selected = 0 ;
                return 0;
		    }
		    else{
		        for(i=5;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    B[i].stone_num+=1;
		        }
		        for(i=0;i<7;i++){
                    A[i].stone_num+=1;
		        }
		        for(i=0;i<carry-23;i++){
                    B[i].stone_num+=1;
		        }
		        if (i==7)
                    player+=1;
                if(B[i-1].stone_num == 1 && i != 7){
                    B[6].stone_num += A[5-(i-1)].stone_num;
                    A[5-(i-1)].stone_num = 0;
                    B[i-1].stone_num = 0;

                }
		        selected = 0 ;
                return 0;
		    }
		    break;
	}
    selected=0;
}

void draw_text(){
    int flag=0;
    for(int i =0;i<6;i++){
        if(A[i].stone_num !=4 || B[i].stone_num != 4)
            flag=1;
    }
    if(flag==0){

        for(int i=0;i<6;i++){
            drawFilledCircle(A[i].center_point_x+0.75,A[i].center_point_y+0.75,0.5);
            drawFilledCircle(A[i].center_point_x-0.75,A[i].center_point_y+0.75,0.5);
            drawFilledCircle(A[i].center_point_x-0.75,A[i].center_point_y-0.75,0.5);
            drawFilledCircle(A[i].center_point_x+0.75,A[i].center_point_y-0.75,0.5);

            drawFilledCircle(B[i].center_point_x+0.75,B[i].center_point_y+0.75,0.5);
            drawFilledCircle(B[i].center_point_x-0.75,B[i].center_point_y+0.75,0.5);
            drawFilledCircle(B[i].center_point_x-0.75,B[i].center_point_y-0.75,0.5);
            drawFilledCircle(B[i].center_point_x+0.75,B[i].center_point_y-0.75,0.5);

        }
    }

    else{

        unsigned char string[]="";

        glColor3f(1., 1., 1.);

        for(int i=0;i<7;i++){
            sprintf((char*)string,"%d",A[i].stone_num);

            glRasterPos2f(A[i].text_x,A[i].text_y);

            int len = strlen((const char*)string);
            for (int j = 0; j < len; j++) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[j]);
            }
        }
        unsigned char string2[] = "";
        for(int i=0;i<7;i++){
            sprintf((char*)string2,"%d",B[i].stone_num);

            glRasterPos2f(B[i].text_x,B[i].text_y);

            int len = strlen((const char*)string2);
            for (int j = 0; j < len; j++) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string2[j]);
            }
        }

    }
    unsigned char string[]="";

    glColor3f(1., 1., 1.);

    for(int i=0;i<6;i++){
        sprintf((char*)string,"%d",i+1);

        glRasterPos2f(A[i].text_x,A[i].text_y-3.5);

        int len = strlen((const char*)string);
        for (int j = 0; j < len; j++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[j]);
        }
        sprintf((char*)string,"F%d",i+1);

        glRasterPos2f(-14.15+(i*5.5),B[i].text_y+3.5);

        len = strlen((const char*)string);
        for (int j = 0; j < len; j++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[j]);
        }
    }



    glRasterPos2f(-20,13.5);
    if (player==1){
        unsigned char string[] = "Turn -> PLAYER 1";
        int len = strlen((char*)string);
        for (int j = 0; j < len; j++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[j]);
        }

    }
    else{
        unsigned char string[] = "Turn -> PLAYER 2";
        int len = strlen((char*)string);
        for (int j = 0; j < len; j++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[j]);
        }
    }


}

void setValues(){
    int i;

    for(i=0;i<6;i++){
        A[i].stone_num=4;
        B[i].stone_num=4;
    }

    A[0].center_point_x = -13.75;
    A[0].center_point_y = -4.0;

    A[1].center_point_x = -8.25;
    A[1].center_point_y = -4.0;

    A[2].center_point_x = -2.75;
    A[2].center_point_y = -4.0;

    A[3].center_point_x = 2.75;
    A[3].center_point_y = -4.0;

    A[4].center_point_x = 8.25;
    A[4].center_point_y = -4.0;

    A[5].center_point_x = 13.75;
    A[5].center_point_y = -4.0;

    B[5].center_point_x = -13.75;
    B[5].center_point_y = 4.0;

    B[4].center_point_x = -8.25;
    B[4].center_point_y = 4.0;

    B[3].center_point_x = -2.75;
    B[3].center_point_y = 4.0;

    B[2].center_point_x = 2.75;
    B[2].center_point_y = 4.0;

    B[1].center_point_x = 8.25;
    B[1].center_point_y = 4.0;

    B[0].center_point_x = 13.75;
    B[0].center_point_y = 4.0;

    A[6].center_point_x = 17.8;
    A[6].center_point_y = 0.0;

    B[6].center_point_x = -18.2;
    B[6].center_point_y = 0.0;

    for(i=0;i<7;i++){
        A[i].text_x = A[i].center_point_x-0.4;
        A[i].text_y = A[i].center_point_y-0.3;

        B[i].text_x = B[i].center_point_x-0.4;
        B[i].text_y = B[i].center_point_y-0.3;
    }
}

void draw_game_board()
{
    glColor3f(0.475,0.259,0.157);
    glBegin(GL_QUADS);

    glVertex2f(20.0f, 15.0f); // vertex 1
    glVertex2f(20.0f, -15.0f); // vertex 2
    glVertex2f(-20.0f, -15.0f); // vertex 3
    glVertex2f(-20.0f, 15.0f); // vertex 4

    glEnd();

    glColor3f(0.722,0.451,0.227);
    glBegin(GL_QUADS);

    glVertex2f(20.0f, 10.0f); // vertex 1
    glVertex2f(20.0f, -10.0f); // vertex 2
    glVertex2f(-20.0f, -10.0f); // vertex 3
    glVertex2f(-20.0f, 10.0f); // vertex 4

    glEnd();

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);

    glVertex2f(-17.0,0.0);
    glVertex2f(17.0,0.0);

    glEnd();

    glColor3f(0.475,0.259,0.157);
    glBegin(GL_QUADS);

    glVertex2f(17.0f, 7.0f); // vertex 1
    glVertex2f(19.0f, 7.0f); // vertex 2
    glVertex2f(19.0f, -7.0f); // vertex 3
    glVertex2f(17.0f, -7.0f); // vertex 4

    glEnd();

    glBegin(GL_QUADS);

    glVertex2f(-19.0f, 7.0f); // vertex 1
    glVertex2f(-17.0f, 7.0f); // vertex 2
    glVertex2f(-17.0f, -7.0f); // vertex 3
    glVertex2f(-19.0f, -7.0f); // vertex 4

    glEnd();

    glMatrixMode(GL_PROJECTION);

    drawFilledCircle(13.75,4.0,2.25);
    drawFilledCircle(8.25,4.0,2.25);
    drawFilledCircle(2.75,4.0,2.25);
    drawFilledCircle(-2.75,4.0,2.25);
    drawFilledCircle(-8.25,4.0,2.25);
    drawFilledCircle(-13.75,4.0,2.25);

    drawFilledCircle(13.75,-4.0,2.25);
    drawFilledCircle(8.25,-4.0,2.25);
    drawFilledCircle(2.75,-4.0,2.25);
    drawFilledCircle(-2.75,-4.0,2.25);
    drawFilledCircle(-8.25,-4.0,2.25);
    drawFilledCircle(-13.75,-4.0,2.25);

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);

    glVertex2f(0.0,7.0);
    glVertex2f(0.0,-7.0);

    glEnd();
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.25f * PI;

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}
