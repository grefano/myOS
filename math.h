#pragma once

#define PI 3.1415
typedef struct{
  int x;
  int y;
} vec2;
double sqrt(double x){

}
double mod(double a, double b){
  while(a > b){
    a-=b;
  }
  return a;
}
int factorial(int a){
  int r = 1;
  for(int i = a; i >= 1; i--){
    r*=i;
  }
  return r;
}
double power(double a, double b){
  for(int i = 1; i < b; i++){
    a *= a;
  }
  return a;
}
double sin(float a){
  a = (float)mod(a, PI);
  return a - power(a,3)/factorial(3) + power(a,5)/factorial(5) - power(a, 7)/factorial(7) + power(a, 9)/factorial(9); 
}
double sinnorm(float a){
  return (sin(a)+1.0)/2.0;
}
double cos(float a){

}

