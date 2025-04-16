// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:				Filters.cpp
// Last Modification Date:	6/10/2023
// Author1 and ID and Group:	20220037
// Author2 and ID and Group:	20220221
// Author3 and ID and Group:	20220410
// Teaching Assistant : No
// Purpose: Put filters on images

#include <bits/stdc++.h>
#include<fstream>
#include "libraries/bmplib.h"
#include "libraries/bmplib.cpp"
#include "colored.cpp"
using namespace std ;

//load function data

unsigned char img_in_Gray[SIZE][SIZE] ;
unsigned char img_out_Gray[SIZE][SIZE] ;
bool is_colored ;

// those functions copy and save images to do the process more than one time

void cpy(){
    for (int i = 0; i < SIZE ; i++ )
        for(int j = 0 ; j < SIZE ; j++ )
            img_in_Gray[i][j] = img_out_Gray[i][j] ;
}

void save_gr() {
    cout<<"Please enter target file name:"<<endl;
    string text ; cin >> text ;
    text = "images/" + text + ".bmp" ;
    writeGSBMP( text.c_str() , img_in_Gray ) ;
}

//=======================================================================

// Filters

//This filter convert images to black and white images

void B_W_F(){
    unsigned char mn = 255 , mx = 0 , avg ;
    // the first nested for loops it is just calculating the minimum and maximum pixels in the image 
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            mn = min( img_in_Gray[i][j] , mn ) ;
            mx = max ( img_in_Gray[i][j] , mx ) ;
        }
    }
    // then we calculate the avg
    avg = ( mn + mx ) / 2 ;
    // the second nested for loops it has a condition if the pixel is bigger than avg the pixel =255 (white) else 0(dark).
    for ( int i = 0 ; i < SIZE ; i++ ) {
        for ( int j = 0; j < SIZE ; j++ ) {
            (img_in_Gray[i][j] > avg) ? img_out_Gray[i][j] = 255 : img_out_Gray[i][j] = 0 ;
        }
    }
    cpy();
}

//This filter invert Grayscale images

void invert_f() {
    // the nested for loop chages every pixel by subtracting 255 from the pixel.
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            img_out_Gray[i][j] = 255 - img_in_Gray[i][j] ;
        }
    }
    cpy();
}

//This filter merge two or more  images

void merge(){
    unsigned char img_in_G[SIZE][SIZE] ;
    cout<<"Please enter name of image file to merge with:"<<"\n";
    char text[1000] = "" ;
    cin >> text ;
    strcat( text , ".bmp") ;
    ifstream in_file( text , std::ifstream::ate | std::ifstream::binary ) ;
    readGSBMP( text , img_in_G ) ;
    // the nested for loop it gets the avrage between the two images and pust the avg int the new image .
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int avg=(img_in_G[i][j]+img_in_Gray[i][j])/2;
            img_out_Gray[i][j]=avg;
        }
    }
    cpy();
}

//This filter flip  images horizontally or vertically

void FLIP_F(){
    cout<<"Flip (h)orizontally or (v)ertically ?\n";
    char c;cin>>c;
    switch (c) {
        // if it is v the nested for loop the array that will be the new image we loop from the last row to the first
        case 'v' :
            for (int i = 0; i <SIZE ; ++i) {
                for (int j = 0; j <SIZE ; ++j) {
                    img_out_Gray[i][j]=img_in_Gray[SIZE-i-1][j]; //
                }
            }
            break;
        // and copy the main image to the copy one and if it is h we loop form the last column to the first .
        case 'h' :
            for (int i = 0; i <SIZE ; ++i) {
                for (int j = 0; j <SIZE ; ++j) {
                    img_out_Gray[i][j]=img_in_Gray[i][SIZE-j-1];
                }
            }
            break;
        default :
            break;
    }
    cpy();
}

//This filter rotate images 90 or 180 or 270 degrees

void Rot_R( ){
    cout << "Rotate (90), (180) or (270) degrees?\n" ; int chc ; cin >> chc ;
    switch ( chc ) {
        // if it is 90 the nested for loop the array that will be the new image we loop from the last column to the first
        case 90 :
            for ( int i = 0 ; i < SIZE ; i++ ){
                for ( int j = 0 ; j < SIZE ; j++ ){
                    img_out_Gray[j][SIZE-i-1] = img_in_Gray[i][j] ;
                }
            }
            break ;
        // if it is 180 we loop form the last column to the first and last row to the first 
        case 180 :
            for ( int i = 0 ; i < SIZE ; i++ ){
                for ( int j = 0 ; j < SIZE ; j++ ){
                    img_out_Gray[SIZE - 1 - i ][SIZE - 1 - j ] = img_in_Gray[i][j] ;
                }
            }
            break ;
        // if it is  270 we loop form the last row to the first 
        case 270 :
            for ( int i = 0 ; i < SIZE ; i++ ){
                for ( int j = 0 ; j < SIZE ; j++ ){
                    img_out_Gray[SIZE - j - 1 ][i] = img_in_Gray[i][j] ;
                }
            }
            break;
        default :
            break;
    }
    // and copy the main image to the copy one
    cpy();
}


//This filter lower or higher the opacity of images

void dark_light(){
    // if it is l  the nested for loop add to every pixel 255 then we divid it over 2 make it bright else if d we just divide 
    // every pixel over 2 to make it darker .
    cout<<"Do you want to (d)darken or (l)lighten?"<<"\n";
    char c; cin >> c;
    switch (c) {
        case 'l' :
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    img_out_Gray[i][j] = (img_in_Gray[i][j] + (255)) / 2;
                }
            }
            break ;
        case 'd' :
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    img_out_Gray[i][j] = img_in_Gray[i][j] / 2;
                }
            }
            break;
        default :
            break ;
    }
    cpy();
}

//This filter is detecting the edges of objects in images

void detect_edges( ){
    // we first copy the image in another array by the first nested loop then 
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            img_out_Gray[i][j] = img_in_Gray[i][j] ;
        }
    }
    // the second nested loop we check if the pixel - the pixel that is in the its row but plus 2 if it is bigger than 53 
    // or the pixel tha is the same column plus 2 is bigger than 40 then convert it to black 0 else convert it to white 255.
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (abs(img_out_Gray[i][j]-img_out_Gray[i][j+2])>40  || abs(img_out_Gray[i][j]-img_out_Gray[i+2][j])>53)
                img_out_Gray[i][j]=0;
            else
                img_out_Gray[i][j]=255;
        }
    }
    cpy();
}

//This filter  enlarges images to (1 or 2 or 3 or 4) quarter

void enlarge(){
    // int this part we ask the user for the quadrant of the image tha he would like to enlarge
    cout << "Which quarter to enlarge 1, 2, 3 or 4?\n" ;
    int chc ; cin >> chc ;
    // this is a directionn to decide which quadrant we will be working on
    // the one that will be used will depend on the uusers choic 
    int dx[] { 0 , 0 ,  SIZE/2  ,  SIZE / 2 };
    int dy[] { 0 , SIZE / 2 , 0 , SIZE / 2  };
    // in this for loop after choosing a quadrant we assign each pixel
    // to 4 pixels in the large image to make it look bigger in the 256 * 256 scale
    for ( int i = 0 ; i < SIZE / 2 ; i++ ){
        for ( int j = 0 ; j < SIZE / 2 ; j++ ){
            unsigned char c = img_in_Gray[i + dx[chc-1]][j+dy[chc-1]] ;
            img_out_Gray[i*2][j*2] = c ;
            img_out_Gray[i*2 + 1 ][j*2] = c ;
            img_out_Gray[i*2][j*2 + 1 ] = c ;
            img_out_Gray[i*2 + 1 ][j*2+ 1] = c ;
        }
    }
    cpy();
}

//This filter shrinks images to (1/2 or 1/3 or 1/4)

void shrink(){
    cout<<"Shrink to (1/2), (1/3) or (1/4)?"<<"\n";
    string s;
    cin>>s;
    // we first make all the pixels white by the first nested for loop the the second nested loop    
    for (int i = 0; i < SIZE; i++ ) {
        for (int j = 0; j < SIZE; j++ ) {
            img_out_Gray[i][j] = 255 ;
        }
    }
    // he second nested loop  it calculate the avg for 4 pixels that around the main pixel then it pusts it
    // in the main pixel row over the shrink number .
    int x = ( s.back() - '0' ) ;
    for (int i = 0; i < SIZE; i+=2) {
        for (int j = 0; j < SIZE; j+=2) {
            img_out_Gray[i/x][j/x]=(img_in_Gray[i][j]+img_in_Gray[i+1][j]+img_in_Gray[i][j+1]+img_in_Gray[i+1][j+1])/4;
        }
    }
    cpy();
}

//This filter make a mirror copy of images to (left or right or upper or down)

void mir(){
    cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n";
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            img_out_Gray[i][j] = img_in_Gray[i][j] ;
        }
    }
    char p ; cin >> p;
    switch ( p ) {
        case 'r' :
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE/2; ++j) {
                    img_out_Gray[i][j]=img_out_Gray[i][SIZE-j-1];
                }
            }
            break;
        case 'l' :
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE/2; ++j) {
                    img_out_Gray[i][SIZE-j-1]=img_out_Gray[i][j];
                }
            }
            break;
        case 'd' :
            for (int i = 0; i < SIZE/2; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    img_out_Gray[i][j]=img_out_Gray[SIZE-i-1][j];
                }
            }
            break;
        case 'u' :
            for (int i = 0; i < SIZE/2; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    img_out_Gray[SIZE-i-1][j]=img_out_Gray[i][j];
                }
            }
            break;
        default :
            break;
    }
    cpy();
}


//This filter shuffle images by a specific order

void shuffle_img( ){
    // this a direction array to decid on which quadrant the we are going to replace the original on with
    // depending on the users input of the new quadrant order the answer will diffre acordingly 
    int dx[] { 0 , 0 , SIZE / 2 , SIZE / 2 } ;
    int dy[] { 0 , SIZE / 2 , 0 , SIZE / 2 } ;
    cout << "New order of quarters ? \n" ;
    vector<int> vv(4) ; for ( int i = 0 ; i < 4 ; i++ ) cin >> vv[i] ;
    // mixing the input after substracting one from it allows us to shuffle the image in a single step 
    for ( int i = 0 ; i < SIZE / 2 ; i++ ) {
        for ( int j = 0 ; j < SIZE / 2 ; j++ ) {
            img_out_Gray[i+dx[0]][j+dy[0]] = img_in_Gray[i+dx[vv[0]-1]][j+dy[vv[0]-1]] ; // 1st quad
            img_out_Gray[i+dx[1]][j+dy[1]] = img_in_Gray[i+dx[vv[1]-1]][j+dy[vv[1]-1]] ; // 2nd quad
            img_out_Gray[i+dx[2]][j+dy[2]] = img_in_Gray[i+dx[vv[2]-1]][j+dy[vv[2]-1]] ; // 3rd quad
            img_out_Gray[i+dx[3]][j+dy[3]] = img_in_Gray[i+dx[vv[3]-1]][j+dy[vv[3]-1]] ; // 4th quad
        }
    }
    cpy();
}

//This filter make a blur copy of images

void blur(){
    // direction array to acsses all pixels in a square area
    int dx[] = {1,0,0,-1,-1,1,-1,1};
    int dy[] = {0,1,-1,0,1,1,-1,-1};
    // we calclulate the sum of the pxels value and divide them by the total number of pixels acssessd
    // getting the avg of those pixels and storing it in the pixel in the middle giving us this blur effect 
    // in order to increase the blur effect we multilpide the direction array coordinate by one to acssess mor pixels
    // giving us a stronger blur effect 
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            unsigned int avg = 1 , rot = img_in_Gray[i][j] ;
            for ( int k = 1 ; k <= 3 ; k++ ) {
                for (int l = 0; l < 8; l++) {
                    int ni = i + dx[l] * k , nj = j + dy[l] * k ;
                    if ((ni >= 0 and nj >= 0 and ni < SIZE and nj < SIZE)) {
                        avg++;
                        rot += img_in_Gray[ni][nj];
                    }
                }
            }
            img_out_Gray[i][j] = ( rot / avg ) ;
        }
    }
    cpy();
}


//This filter crops images

void crop(){
    cout<<"Please enter x y l w \n";
    int x , y , l , w ; cin >> x >> y >> l >> w;
    // we first the copy image all white by the first nested loop then     
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            img_out_Gray[i][j] = 255 ;
        }
    }
    // the second nested loop to change the location of  croped image to the center .
    for (int i = x ; i <= l && i < SIZE ; i++ ) {
        for (int j = y; j <= w && j < SIZE ; j++ ) {
            img_out_Gray[ (i - x) + ( ( SIZE - l ) / 2 ) + 1 ][ (j - y) + ( ( SIZE - w ) / 2 ) ] = img_in_Gray[i][j] ;
        }
    }
    cpy();
}


//This filter skew (stretch) images horizontally with a given degree

void skew_r(){
    // we take the angle of inclination 
    cout<<"Please enter degree to skew right :\n";
    unsigned char temp_img[SIZE][SIZE] ;
    double rad ;  cin >> rad ;
    rad = ( rad * 22 ) / ( 180 * 7 ) ;
    // we calculate the size of the base after shrinking to based on the angle given to us by the user 
    int s = (int)(( 256 * 256 )/(( 256 / tan(rad) ) + 256 )) ;
    double mov = SIZE - s ; double step = ( 256.0 - s ) / 256.0  ;
    // changing the color of the background to white  
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            img_out_Gray[i][j] = 255 ;
            temp_img[i][j] = 255 ;
        }
    }
    // shrinking the image 
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < s ; j++ ){
            temp_img[i][j] = img_in_Gray[i][(j*255)/s] ;
        }
    }
    // shifting each line of pixels by mov 
    // and substracting step from mov after each line 
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < s ; j++ ){ img_out_Gray[i][j+(int)mov] = temp_img[i][j] ; }
        mov -= step ;
    }
    cpy();
}

//This filter skew (stretch) images vertically with a given degree

void skew_u(){
    cout<<"Please enter degree to skew Up: ";
    // we take the angle of inclination 
    double rad ; cin>> rad ;
    unsigned char temp[SIZE][SIZE];
    rad =( rad *22)/(180*7);
    // we calculate the size of the base after shrinking to based on the angle given to us by the user 
    int s = (int)((256*256)/((256 / tan(rad ))+256)) ;
    double move=SIZE-s; double stp=(256.0-s)/256.0;
    // changing the color of the background to white
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            img_out_Gray[i][j] = 255 ;
            temp[i][j] = 255 ;
        }
    }
    // shrinking the image 
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < s ; j++ ){
            temp[i][j] = img_in_Gray[(j*255)/s][i] ;
        }
    }
    // and substracting step from mov after each line
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < s ; j++ ){ img_out_Gray[j+(int)move][i] = temp[i][j] ; }
        move -= stp ;
    }
    cpy();
}

// ======================================================================

// image load functions and the menu (options) for filters

void load(){
    cout<<"Please enter file name of the img to process:"<<'\n';
    string text ; cin >> text ;
    text = "images/" + text + ".bmp" ;
    ifstream in_file( text , std::ifstream::ate | std::ifstream::binary ) ;
    if ( in_file.tellg() > 196000 ) is_colored = true ;
    if ( is_colored ) readRGBBMP(text.c_str() , img_in_color );
    else readGSBMP( text.c_str() , img_in_Gray ) ;
}

bool option(){
    char chc ; cin >> chc ;
    switch( chc ) {
        case '1' :
            if (is_colored)
                B_W_F_cl();
            else
                B_W_F();
            break ;
        case '2' :
            if (is_colored)
                invert_f_cl();
            else
                invert_f();
            break;
        case '3' :
            if (is_colored)
                merge_cl();
            else
                merge();
            break ;
        case '4' :
            if (is_colored)
                FLIP_F_cl();
            else
                FLIP_F();
            break ;
        case '5' :
            if (is_colored)
                Rot_R_cl();
            else
                Rot_R();
            break ;
        case '6' :
            if (is_colored)
                dark_light_cl();
            else
                dark_light();
            break ;
        case '7' :
            if (is_colored)
                detect_edges_cl();
            else
                detect_edges();
            break ;
        case '8' :
            if (is_colored)
                enlarge_cl();
            else
                enlarge();
            break ;
        case '9' :
            if (is_colored)
                shrink_cl();
            else
                shrink();
            break ;
        case 'a' :
            if (is_colored)
                mir_cl();
            else
                mir();
            break ;
        case 'b' :
            if (is_colored)
                shuffle_img_cl();
            else
                shuffle_img();
            break ;
        case 'c' :
            if (is_colored)
                blur_cl();
            else
                blur();
            break ;
        case 'd' :
            if (is_colored)
                crop_cl();
            else
                crop();
            break ;
        case 'e' :
            if (is_colored)
                skew_r_cl();
            else
                skew_r();
            break ;
        case 'f' :
            if (is_colored)
                skew_u_cl();
            else
                skew_u();
            break;
        case 's' :
            if (is_colored)
                save_clr();
            else
                save_gr();
            break;
        case 'l' :
            is_colored = false;
            load();
            break ;
        default :
            return true ;
            break ;
    }
    return false ;
}

void menu(){
    cout<<"Please select a filter to apply or 0 to exit :"<<'\n';
    cout<<"1 Black & White Filter           6 Darken and Lighten Image\n"
          "2 Invert Filter                  7 Detect Image Edges \n"
          "3 Merge Filter                   8 Enlarge Image\n"
          "4 Flip Image                     9 Shrink Image\n"
          "5 Rotate Image                   a Mirror 1/2 Image\n"
          "b Shuffle Image                  e Skew Image Right  \n"
          "c Blur Image                     f Skew Image Up  \n"
          "d Crop Image                     l- load a new image \n"
          "0 Exit                           s- Save the img to a file \n";
    if ( option() ) return ;
    menu() ;
}

// ======================================================================

int main(){
    load() ;
    menu() ;
    return 0 ;
}
