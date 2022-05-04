void trigono_xyz(float x, float y, float z)
{
 L1=sqrt(sq(x)+sq(y));
 Serial.print("L1 : ");
 Serial.println(L1);
 gama=atan(x/y)/PI*180;
 L=sqrt(sq(L1-cx)+sq(z));
 beta=acos((sq(tb)+sq(fm)-sq(L))/(2*tb*fm))/PI*180;
 alpha1=acos(z/L)/PI*180;
 alpha2=acos((sq(fm)+sq(L)-sq(tb))/(2*fm*L))/PI*180;
 alpha=alpha1+alpha2;

 gama= gama+105.00;
 alpha = alpha+60 ;
 beta = beta-30;
}
