#include <stdio.h>
#include <conio.h>
// --------------------------------------- Mulitplication Function ------------------------------
// int main() {
//     printf("Multiplication Program \n");
//     int x , y , z;
//     printf("Enter a number:");
//     scanf("%d" , &x);
//     printf("Enter a number:");
//     scanf("%d" , &y);
//     z = x * y;
//     printf("result : %d", z);
//     getch();
// }
// ------------------------------------------- Area of Rectangle ------------------------------
// int main() {
//     printf("Area Of Rectangle: \n");
//     int w , h , r;
//     printf("Enter a width:");
//     scanf("%d", &w);
//     printf("Enter a length:");
//     scanf("%d", &h);
//     r = w * h;
//     printf("Result: %d", r / 9);
//     getch();
// };
// ====================================== Muliplication Function ================================
// int add(int a , int b) {
//     int c ;
//     c = a * b;
//     return c;
// };

// int main() {
//     int x = 2  , y = 2 , res;
//     printf("Enter a two number:\n");
//     printf("Enter a number:");
//     scanf("%d", &x);
//     printf("Enter a number");
//     scanf("%d", &y);
//     res = add(x,y);
//     printf("Print a Result: %d" , res);
//     return 0;
// };
// =========================== Find the bug =========================================
// void main() {
//     char ch , ch , sum;
//     clrscr();
//     ch="a";
//     ch="b";
//     sum = ch + ch;
//     printf("sum = %d", sum);
//     getch();
// };

// ========================== warning this is a infanite loop ==================================
// int main() {
//     for(int n = 10; n >= 10; n++) {
//         printf("hello sir %d",n);
//     };
// };

// ------------------------------------ pattren programming -----------------------------------
// int main() { 
// int i , j , s;
// for(i = 15; i >= 1; i--) {
//     for(s = 1; s <= 15-i; s++) {
//         printf(" ");
//     }
//     for(j = 1; j <= i; j++) {
//         printf("*");
//     }
//     printf("\n");
// }
// };

// ================================== pattren programming =======================================
// int main() {
//     int i,j,s;
//     for(i = 1; i <= 15; i++) {
//         for(s = 1; s <= 15-i; s++){
//             printf(" ");
//         }
//         for(j = 1; j <= i; j++) {
//             printf("*");
//         };
//         printf("\n");
//     };
// };
// -------------------------- Calculate the area of triangle ------------------------------
// int main() {
//     float base , height;
//     double area;
//     printf("Enter the base:");
//     scanf("%f", &base);
//     printf("Enter the height:");
//     scanf("%f", &height);
//     area = 0.5 * base * height;
//     printf("Result is: %5.2f\n", area);
//     getch();
//     return 0;
// };


// int main() {
//     char a[] = "                   ";
//     printf("Enter the charcters:");
//     scanf("%c", &a);
//     printf("The ACII code is %c%d",a,a);
//     getch();
//     return 0;
// }
 
// ============================= test and check the error ===============================
// int main() {
//         char vovels = "";
//         printf("Check the Vovels Characters:");
//         scanf("%c",&vovels);
//         if(vovels == "a" || vovels == "A" || vovels == "e" || vovels == "E" || vovels == "i" || vovels == "I" || vovels == "o" || vovels == "O" || vovels == "u" || vovels == "U") {
//             printf("%cThis is a vovels:", vovels);
//         } else {
//             printf("%cThis is not vovels:", vovels);
//         };
    
//     return 0;
// };

// ============================ find the grather number =================================
// int main() {
//     int a , b , c;
//     printf("Enter a three number:");
//     scanf("%d%d%d", &a, &b, &c);
//     if(a>b && a>c) {
//         printf("%d is grather then %d and %d", a,b,c);
//     }else if(b>a && b>c) {
//         printf("%d is grather then %d and %d", b,a,c);
//     } else if(a == b && b == c && c == a) {
//         printf("Both are equel %d %d %d",a,b,c);
//     } else {
//         printf("%d is grather then %d and %d", c,a,b);
//     };
//     return 0;
// };

// int main() {
//     int x = 4;
//     ++x;
//     printf("%d",x);
//     return 0;
// };

// int main() {
//     int i , j;
//     for(i = 1; i > 31; i--) {
//       for(j = 1; j <= i; j++) {
//         printf("%d ",j);
//       };
//       printf("\n");
//     };
// };

// int main() {
//     int a , b;
//     for(a=11; a>=1; a--) {
//         for(b=1; b<a; b++) {
//             printf("%d ",b);
//         }
//         printf("\n");
//     }
//     return 0;
// }

int main() {
    int arr[4];
    int i;
    float s;
    float per;

    for(i = 0; i < 5; i++) {
        scanf("%d", &arr[i]);
    }
    
        switch(arr[i]) {
        case 0:
            printf("Enter the English subject number:");
            break;
        case 1:
            printf("Enter the Urdu subject number:");
            break;
        case 2:
            printf("Enter the Maths subject number:");
            break;
        case 3:
            printf("Enter the Economic subject number:");
            break;
        case 4:
            printf("Enter the Computer subject number:");
            break;
        default:
            printf("Invalid input");
    }

    for(i = 0; i < 5; i++) {
        s = s + arr [i];
    }
    printf("Total Number: %5.0f\n",s);
    per = (s / 550) * 100;
    printf("Persantage is: %5.2f ",per);
    return 0;
}