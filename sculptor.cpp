#include <string>
#include <iostream>
#include <fstream>
#include <sculptor.h>
#include <cstdlib>
#include <vector>
#include <mainwindow.h>

/**
* @file sculptor.cpp
* @brief this source file will contain all required
* definitions for drawing and removing voxels iin the sculptor objetc.
*
* @author Reyne Jasson
*
* @date 20/06/2019
*/

using namespace std;

Sculptor::Sculptor(int tx, int ty, int tz){
    nx=tx; ny=ty; nz=tz;
    v= new Voxel**[nx];
    if(v == nullptr){
        cout<<"v não armazenado"<<endl;
        exit(0);
    }
    v[0]= new Voxel*[nx*ny] ;
    if(v[0] == nullptr){
        cout<<"v[0] não armazenado"<<endl;
        exit(0);
    }
    v[0][0]= new Voxel[nx*ny*nz];
    if(v[0][0]==nullptr){
        cout<<"v[0][0] não armazenado"<<endl;
        exit(0);
    }

    for (int i=0;i<nx;i++){
        if(i<(nx-1)){
            v[i+1]=v[i]+ny;
        }
        for (int j=0;j<ny;j++){
            if(j==ny-1&&i!=(nx-1)){
                v[i+1][0]=v[i][j]+nz;
            }
            else{
                v[i][j+1]=v[i][j]+nz;
            }

            for(int k=0;k<nz;k++){
                v[i][j][k].r=0.0;
                v[i][j][k].g=0.0;
                v[i][j][k].b=0.0;
                v[i][j][k].a=0.0;
                v[i][j][k].isOn=false;
            }

        }
    }

    cout<<"escultor criado com sucesso"<<endl;
}
Sculptor::~Sculptor(){
    delete [] v[0][0];
    delete [] v[0];
    delete [] v;
    cout<<"sculptor deletado com sucesso"<<endl;
}
void Sculptor::setColor(float _r, float _g, float _b, float alpha)
{
    if(r<0||g<0||b<0||alpha<0){
        cout<<"Parametros de 'setColor' invalidos"<<endl;
        //exit(1);
    }
    r=_r;
    g=_g;
    b=_b;
    a=alpha;
}
void Sculptor::putVoxel( int x, int y, int z)
{
    if(x>=nx||x<0||y>=ny||y<0||z>=nz||z<0){
        cout<<"Parâmetros em 'putVoxel' inválidos"<<endl;
        return;
    }


    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;


}
void Sculptor::cutVoxel( int x, int y, int z)
{
    if(x>=nx||x<0||y>=ny||y<0||z>=nz||z<0){
        cout<<"Parâmetros em 'cutVoxel' inválidos"<<endl;
        return;
    }
    v[x][y][z].isOn = false;

}
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for(int i=x0; i<=x1; i++){
        for(int j=y0; j<=y1; j++){
            for (int k=z0; k<=z1; k++) {
                putVoxel(i,j,k);
            }
        }
    }
}
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for(int i=x0; i<=x1; i++){
        for(int j=y0; j<=y1; j++){
            for (int k=z0; k<=z1; k++) {
                cutVoxel(i,j,k);

            }
        }
    }
}
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{

    float dx,dy,dz;
    for(int i=0; i<nx; i++){
        dx=((static_cast<float>(i)-xcenter)/radius)*((static_cast<float>(i)-xcenter)/radius);
        for(int j=0; j<ny; j++){
            dy=((static_cast<float>(j)-ycenter)/radius)*((static_cast<float>(j)-ycenter)/radius);
            for (int k=0; k<nz; k++) {
                dz=((static_cast<float>(k)-zcenter)/radius)*((static_cast<float>(k)-zcenter)/radius);

                if(dx+dy+dz<=1){
                    putVoxel(i,j,k);

                }
            }
        }
    }
}
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    float dx,dy,dz;
    for(int i=0; i<nx; i++){
        dx=((static_cast<float>(i)-xcenter)/radius)*((static_cast<float>(i)-xcenter)/radius);
        for(int j=0; j<ny; j++){
            dy=((static_cast<float>(j)-ycenter)/radius)*((static_cast<float>(j)-ycenter)/radius);
            for (int k=0; k<nz; k++) {
                dz=((static_cast<float>(k)-zcenter)/radius)*((static_cast<float>(k)-zcenter)/radius);
                if(dx+dy+dz<=1){
                     cutVoxel(i,j,k);
                }
            }
        }
    }
}
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    float dx,dy,dz;
    for(int i=0; i<nx; i++){
        dx=((static_cast<float>(i)-xcenter)/rx)*((static_cast<float>(i)-xcenter)/rx);
        for(int j=0; j<ny; j++){
            dy=((static_cast<float>(j)-ycenter)/ry)*((static_cast<float>(j)-ycenter)/ry);
            for (int k=0; k<nz; k++) {
                dz=((static_cast<float>(k)-zcenter)/rz)*((static_cast<float>(k)-zcenter)/rz);
                if(dx+dy+dz<=1){
                    putVoxel(i,j,k);
                }
            }
        }
    }
}
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    float dx,dy,dz;
    for(int i=0; i<nx; i++){
        dx=((static_cast<float>(i)-xcenter)/rx)*((static_cast<float>(i)-xcenter)/rx);
        for(int j=0; j<ny; j++){
            dy=((static_cast<float>(j)-ycenter)/ry)*((static_cast<float>(j)-ycenter)/ry);
            for (int k=0; k<nz; k++) {
                dz=((static_cast<float>(k)-zcenter)/rz)*((static_cast<float>(k)-zcenter)/rz);
                if(dx+dy+dz<=1){
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}
void Sculptor::writeOFF(const string filename)
{
    char ***check;
    check=new char**[nx];
    if(check == nullptr){
        cout<<"check não armazenado"<<endl;
        exit(0);
    }
    check[0]= new char*[nx*ny] ;
    if(check[0] == nullptr){
        cout<<"check[0] não armazenado"<<endl;
        exit(0);
    }
    check[0][0]= new char[nx*ny*nz];
    if(check[0][0]==nullptr){
        cout<<"check[0][0] não armazenado"<<endl;
        exit(0);
    }

    for (int i=0;i<nx;i++){
        if(i<(nx-1)){
            check[i+1]=check[i]+ny;
        }
        for (int j=0;j<ny;j++){
            if(j==ny-1&&i!=(nx-1)){
                check[i+1][0]=check[i][j]+nz;
            }
            else{
                check[i][j+1]=check[i][j]+nz;
            }
            for(int k=0;k<nz;k++){
                check[i][j][k]='0';
            }
        }
    }

    for(int i=1;i<(nx-1);i++){
        for (int j=1;j<(ny-1);j++) {
            for(int k=1; k<(nz-1);k++){
                if(v[i-1][j][k].isOn && v[i+1][j][k].isOn && v[i][j-1][k].isOn &&
                   v[i][j+1][k].isOn && v[i][j][k-1].isOn && v[i][j][k+1].isOn){
                    check[i][j][k]='1';
                }
            }
        }
    }
    for(int i=1;i<(nx-1);i++){
        for (int j=1;j<(ny-1);j++) {
            for(int k=1; k<(nz-1);k++){
                if(check[i][j][k]=='1'){
                    v[i][j][k].isOn=false;
                }
            }
        }
    }
    delete [] check[0][0];
    delete [] check[0];
    delete [] check;

    int Nf,Nv, Nvox=0 ,nfc=0, face;
    ofstream file;
    file.open(filename);
    if(file.is_open()){
        cout<<"Saving OFF"<<endl;
    }
    else{
        cout << "arquivo off nao foi aberto"<<endl;
        exit(1);
    }
    file<<"OFF \n";

    for (int i=0;i<nx;i++) {
        for (int j=0;j<ny;j++) {
            for (int k=0;k<nz;k++) {
                if(v[i][j][k].isOn){
                    Nvox++;
                }
            }
        }
    }

    Nf=6*Nvox;
    Nv=8*Nvox;

    file<<Nv<<" "<<Nf<<" 0 \n";

    double lowX,highX,lowY,highY,lowZ,highZ;

    for(int k=0;k<nz; k++){
        lowZ=-0.5+k;
        highZ=0.5+k;
        for(int j=0;j<ny;j++){
            lowY=-0.5+j;
            highY=0.5+j;
            for (int i=0;i<nx;i++) {
                lowX=-0.5+i;
                highX=0.5+i;
                if(v[i][j][k].isOn){
                    file<<lowX<<" "<<highY<<" "<<lowZ<<endl
                        <<lowX<<" "<<lowY<<" "<<lowZ<<endl
                        <<highX<<" "<<lowY<<" "<<lowZ<<endl
                        <<highX<<" "<<highY<<" "<<lowZ<<endl
                        <<lowX<<" "<<highY<<" "<<highZ<<endl
                        <<lowX<<" "<<lowY<<" "<<highZ<<endl
                        <<highX<<" "<<lowY<<" "<<highZ<<endl
                        <<highX<<" "<<highY<<" "<<highZ<<endl;
                }
            }
        }

    }

    for(int k=0;k<nz; k++){
        for(int j=0;j<ny;j++){
            for (int i=0;i<nx;i++) {
                if(v[i][j][k].isOn){
                    face=nfc*8;
                    file<<"4 "<<0+face<<" "<<3+face<<" "<<2+face<<" "<<1+face<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl
                        <<"4 "<<4+face<<" "<<5+face<<" "<<6+face<<" "<<7+face<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl
                        <<"4 "<<0+face<<" "<<1+face<<" "<<5+face<<" "<<4+face<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl
                        <<"4 "<<0+face<<" "<<4+face<<" "<<7+face<<" "<<3+face<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl
                        <<"4 "<<3+face<<" "<<7+face<<" "<<6+face<<" "<<2+face<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl
                        <<"4 "<<1+face<<" "<<2+face<<" "<<6+face<<" "<<5+face<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    nfc++;
                }


            }
        }

    }

    file.close();
}
void Sculptor::writeVECT(const string filename)
{
    char ***check;
    check=new char**[nx];
    if(check == nullptr){
        cout<<"check não armazenado"<<endl;
        exit(0);
    }
    check[0]= new char*[nx*ny] ;
    if(check[0] == nullptr){
        cout<<"check[0] não armazenado"<<endl;
        exit(0);
    }
    check[0][0]= new char[nx*ny*nz];
    if(check[0][0]==nullptr){
        cout<<"check[0][0] não armazenado"<<endl;
        exit(0);
    }

    for (int i=0;i<nx;i++){
        if(i<(nx-1)){
            check[i+1]=check[i]+ny;
        }
        for (int j=0;j<ny;j++){
            if(j==ny-1&&i!=(nx-1)){
                check[i+1][0]=check[i][j]+nz;
            }
            else{
                check[i][j+1]=check[i][j]+nz;
            }
            for(int k=0;k<nz;k++){
                check[i][j][k]='0';
            }
        }
    }

    for(int i=1;i<(nx-1);i++){
        for (int j=1;j<(ny-1);j++) {
            for(int k=1; k<(nz-1);k++){
                if(v[i-1][j][k].isOn && v[i+1][j][k].isOn && v[i][j-1][k].isOn &&
                   v[i][j+1][k].isOn && v[i][j][k-1].isOn && v[i][j][k+1].isOn){
                    check[i][j][k]='1';
                }
            }
        }
    }
    for(int i=1;i<(nx-1);i++){
        for (int j=1;j<(ny-1);j++) {
            for(int k=1; k<(nz-1);k++){
                if(check[i][j][k]=='1'){
                    v[i][j][k].isOn=false;
                }
            }
        }
    }
    delete [] check[0][0];
    delete [] check[0];
    delete [] check;

    ofstream file;
    file.open(filename);
    if(file.is_open()){
        cout<<"Saving VECT"<<endl;
    }
    else{
        cout << "arquivo vect não foi aberto"<<endl;
        exit(1);
    }
    file<<"VECT \n";
    int  Nvox=0;
    for (int i=0;i<nx;i++) {
        for (int j=0;j<ny;j++) {
            for (int k=0;k<nz;k++) {
                if(v[i][j][k].isOn){
                    Nvox++;
                }
            }
        }
    }


    file<<Nvox<<" "<<Nvox<<" "<<Nvox<<endl;
    for(int j=0;j<2;j++){
        for (int i = 0; i< Nvox; i++){
            file<<"1 ";
        }
        file<<"\n";
    }
    for(int i = 0; i<nx; i++){
        for(int j =0 ; j < ny ; j++){
            for (int k=0; k< nz; k++){
                if(v[i][j][k].isOn){
                file<<i<<" "<<j<<" "<<k<<endl;
                }
            }
        }
    }
    for(int i = 0; i<nx; i++){
        for(int j =0 ; j < ny ; j++){
            for (int k=0; k< nz; k++){
                if(v[i][j][k].isOn){
                    file<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                }

            }
        }
    }

    file.close();

}
std::vector<std::vector<Voxel>> Sculptor::readMx(int dim, int plane){
    vector<vector<Voxel>>matriz;
    vector<Voxel> linha;

    switch(plane)
    {
    case 1:  //XY1
        linha.resize(ny);

        for(int i = 0; i<nx; i++){
            for (int j = 0; j < ny; ++j) {
                linha[j].r=v[i][j][dim].r;
                linha[j].g=v[i][j][dim].g;
                linha[j].b=v[i][j][dim].b;
                linha[j].a=v[i][j][dim].a;
                linha[j].isOn=v[i][j][dim].isOn;
            }

            matriz.push_back(linha);
        }
    break;

    case 2:  //ZX1
        linha.resize(nx);

        for(int i = 0; i<nz; i++){
            for (int j = 0; j < nx; ++j) {
                linha[j].r=v[j][dim][i].r;
                linha[j].g=v[j][dim][i].g;
                linha[j].b=v[j][dim][i].b;
                linha[j].a=v[j][dim][i].a;
                linha[j].isOn=v[j][dim][i].isOn;
            }

            matriz.push_back(linha);
        }
    break;

    case 3:  //YZ1
        linha.resize(nz);

        for(int i = 0; i<ny; i++){
            for (int j = 0; j < nz; ++j) {
                linha[j].r=v[dim][i][j].r;
                linha[j].g=v[dim][i][j].g;
                linha[j].b=v[dim][i][j].b;
                linha[j].a=v[dim][i][j].a;
                linha[j].isOn=v[dim][i][j].isOn;
            }

            matriz.push_back(linha);
        }
   break;

    case 4:  //XY2
        linha.resize(nx);

        for(int i = 0; i<ny; i++){
            for (int j=0; j<nx ; j++) {
                int newI=ny-1-i;
                linha[j].r=v[j][newI][dim].r;
                linha[j].g=v[j][newI][dim].g;
                linha[j].b=v[j][newI][dim].b;
                linha[j].a=v[j][newI][dim].a;
                linha[j].isOn=v[j][newI][dim].isOn;
            }

            matriz.push_back(linha);
        }
    break;

    case 5:  //ZX2
        linha.resize(nz);

        for(int i = 0; i<nx; i++){
            for (int j = 0; j <nz; j++) {
                int newI=nx-1-i;
                linha[j].r=v[newI][dim][j].r;
                linha[j].g=v[newI][dim][j].g;
                linha[j].b=v[newI][dim][j].b;
                linha[j].a=v[newI][dim][j].a;
                linha[j].isOn=v[newI][dim][j].isOn;
            }

            matriz.push_back(linha);
        }
   break;
    case 6:  //YZ2
        linha.resize(ny);

        for(int i = 0; i<nz; i++){
            for (int j = 0; j<ny; j++) {
                int newI=nz-1-i;
                linha[j].r=v[dim][j][newI].r;
                linha[j].g=v[dim][j][newI].g;
                linha[j].b=v[dim][j][newI].b;
                linha[j].a=v[dim][j][newI].a;
                linha[j].isOn=v[dim][j][newI].isOn;
            }

            matriz.push_back(linha);
        }
   break;
    case 7:  //XY3
        linha.resize(ny);

        for(int i = 0; i<nx; i++){
            for (int j = 0; j<ny; j++) {
                int newI = nx-1-i;
                int newJ= ny-1-j;
                linha[j].r=v[newI][newJ][dim].r;
                linha[j].g=v[newI][newJ][dim].g;
                linha[j].b=v[newI][newJ][dim].b;
                linha[j].a=v[newI][newJ][dim].a;
                linha[j].isOn=v[newI][newJ][dim].isOn;
            }

            matriz.push_back(linha);
        }
   break;
    case 8:  //ZX3
        linha.resize(nx);

        for(int i=0; i<nz; i++){
            for (int j = 0; j<nx; j++) {
                int newI = nz-1-i;
                int newJ= nx-1-j;
                linha[j].r=v[newJ][dim][newI].r;
                linha[j].g=v[newJ][dim][newI].g;
                linha[j].b=v[newJ][dim][newI].b;
                linha[j].a=v[newJ][dim][newI].a;
                linha[j].isOn=v[newJ][dim][newI].isOn;
            }

            matriz.push_back(linha);
        }
   break;
    case 9:  //YZ3
        linha.resize(nz);

        for(int i = 0; i<ny; i++){
            for (int j = 0; j<nz; j++) {
                int newI = ny-1-i;
                int newJ= nz-1-j;
                linha[j].r=v[dim][newI][newJ].r;
                linha[j].g=v[dim][newI][newJ].g;
                linha[j].b=v[dim][newI][newJ].b;
                linha[j].a=v[dim][newI][newJ].a;
                linha[j].isOn=v[dim][newI][newJ].isOn;
            }

            matriz.push_back(linha);
        }
   break;
    case 10:  //XY4
        linha.resize(nx);

        for(int i = 0 ; i<ny; i++){
            for (int j = 0; j < nx; j++) {
                int newJ = nx-1-j;
                linha[j].r=v[newJ][i][dim].r;
                linha[j].g=v[newJ][i][dim].g;
                linha[j].b=v[newJ][i][dim].b;
                linha[j].a=v[newJ][i][dim].a;
                linha[j].isOn=v[newJ][i][dim].isOn;
            }

            matriz.push_back(linha);
        }
   break;
    case 11:  //ZX4
        linha.resize(nz);

        for(int i = 0; i<nx; i++){
            for (int j = 0; j < nz; j++) {
                int newJ= nz-1-j;
                linha[j].r=v[i][dim][newJ].r;
                linha[j].g=v[i][dim][newJ].g;
                linha[j].b=v[i][dim][newJ].b;
                linha[j].a=v[i][dim][newJ].a;
                linha[j].isOn=v[i][dim][newJ].isOn;
            }

            matriz.push_back(linha);
        }
   break;
    case 12:  //YZ4
        linha.resize(ny);

        for(int i = 0; i<nz; i++){
            for (int j = 0; j < ny; j++) {
                int newJ= ny-1-j;
                linha[j].r=v[dim][newJ][i].r;
                linha[j].g=v[dim][newJ][i].g;
                linha[j].b=v[dim][newJ][i].b;
                linha[j].a=v[dim][newJ][i].a;
                linha[j].isOn=v[dim][newJ][i].isOn;
            }

            matriz.push_back(linha);
        }
   break;
        ////////////////////////////////
    case 13:  //YX1
        linha.resize(nx);

        for(int i = 0; i<ny; i++){
            for (int j = 0; j < nx; ++j) {
                linha[j].r=v[j][i][dim].r;
                linha[j].g=v[j][i][dim].g;
                linha[j].b=v[j][i][dim].b;
                linha[j].a=v[j][i][dim].a;
                linha[j].isOn=v[j][i][dim].isOn;
            }

            matriz.push_back(linha);
        }
    break;

    case 14:  //XZ1
        linha.resize(nz);

        for(int i = 0; i<nx; i++){
            for (int j = 0; j < nz; ++j) {
                linha[j].r=v[i][dim][j].r;
                linha[j].g=v[i][dim][j].g;
                linha[j].b=v[i][dim][j].b;
                linha[j].a=v[i][dim][j].a;
                linha[j].isOn=v[i][dim][j].isOn;
            }

            matriz.push_back(linha);
        }
    break;

    case 15:  //ZY1
        linha.resize(ny);

        for(int i = 0; i<nz; i++){
            for (int j = 0; j < ny; j++) {
                linha[j].r=v[dim][j][i].r;
                linha[j].g=v[dim][j][i].g;
                linha[j].b=v[dim][j][i].b;
                linha[j].a=v[dim][j][i].a;
                linha[j].isOn=v[dim][j][i].isOn;
            }

            matriz.push_back(linha);
        }
   break;

    case 16:  //YX2
        linha.resize(ny);

        for(int i = 0; i<nx; i++){
            for (int j = 0; j<ny ; j++) {
                int jnovo=ny-1-j;
                linha[j].r=v[i][jnovo][dim].r;
                linha[j].g=v[i][jnovo][dim].g;
                linha[j].b=v[i][jnovo][dim].b;
                linha[j].a=v[i][jnovo][dim].a;
                linha[j].isOn=v[i][jnovo][dim].isOn;
            }

            matriz.push_back(linha);
        }
    break;

    case 17:  //XZ2
        linha.resize(nx);

        for(int i = 0; i<nz; i++){
            for (int j = 0; j < nx; j++) {
                int jnovo=nx-1-j;
                linha[j].r=v[jnovo][dim][i].r;
                linha[j].g=v[jnovo][dim][i].g;
                linha[j].b=v[jnovo][dim][i].b;
                linha[j].a=v[jnovo][dim][i].a;
                linha[j].isOn=v[jnovo][dim][i].isOn;
            }

            matriz.push_back(linha);
        }
   break;
    case 18:  //ZY2
        linha.resize(nz);

        for(int i = 0; i<ny; i++){
            for (int j = 0; j <nz; j++) {
                int jnovo=nz-1-j;
                linha[j].r=v[dim][i][jnovo].r;
                linha[j].g=v[dim][i][jnovo].g;
                linha[j].b=v[dim][i][jnovo].b;
                linha[j].a=v[dim][i][jnovo].a;
                linha[j].isOn=v[dim][i][jnovo].isOn;
            }

            matriz.push_back(linha);
        }
   break;
    case 19:  //YX3
        linha.resize(nx);

        for(int i = 0; i<ny; i++){
            for (int j = 0; j <nx; j++) {
                int inovo=ny-1-i;
                int jnovo=nx-1-j;

                linha[j].r=v[inovo][jnovo][dim].r;
                linha[j].g=v[inovo][jnovo][dim].g;
                linha[j].b=v[inovo][jnovo][dim].b;
                linha[j].a=v[inovo][jnovo][dim].a;
                linha[j].isOn=v[inovo][jnovo][dim].isOn;
            }

            matriz.push_back(linha);
        }
   break;
    case 20:  //XZ3
        linha.resize(nz);

        for(int i = 0; i<nx; i++){
            for (int j = 0; j<nz; j++) {
                int inovo=nx-1-i;
                int jnovo=nz-1-j;
                linha[j].r=v[inovo][dim][jnovo].r;
                linha[j].g=v[inovo][dim][jnovo].g;
                linha[j].b=v[inovo][dim][jnovo].b;
                linha[j].a=v[inovo][dim][jnovo].a;
                linha[j].isOn=v[i][dim][j].isOn;
            }

            matriz.push_back(linha);
        }
   break;
    case 21:  //ZY3
        linha.resize(ny);

        for(int i = 0; i<nz; i++){
            for (int j =0; j<ny; j++) {
                int inovo=nz-1-i;
                int jnovo=ny-1-j;
                linha[j].r=v[dim][inovo][jnovo].r;
                linha[j].g=v[dim][inovo][jnovo].g;
                linha[j].b=v[dim][inovo][jnovo].b;
                linha[j].a=v[dim][inovo][jnovo].a;
                linha[j].isOn=v[dim][inovo][jnovo].isOn;
            }

            matriz.push_back(linha);
        }
   break;
    case 22:  //YX4
        linha.resize(ny);

        for(int i =0 ; i<nx; i++){
            for (int j = 0; j < ny; j++) {
                int inovo=nx-1-i;
                linha[j].r=v[inovo][j][dim].r;
                linha[j].g=v[inovo][j][dim].g;
                linha[j].b=v[inovo][j][dim].b;
                linha[j].a=v[inovo][j][dim].a;
                linha[j].isOn=v[inovo][j][dim].isOn;
            }

            matriz.push_back(linha);
        }
   break;
    case 23:  //XZ4
        linha.resize(nx);

        for(int i = 0; i<nz; i--){
            for (int j = 0; j < nx; j++) {
                int inovo=nz-1-i;
                linha[j].r=v[j][dim][inovo].r;
                linha[j].g=v[j][dim][inovo].g;
                linha[j].b=v[j][dim][inovo].b;
                linha[j].a=v[j][dim][inovo].a;
                linha[j].isOn=v[j][dim][inovo].isOn;
            }

            matriz.push_back(linha);
        }
   break;
    case 24:  //ZY4
        linha.resize(nz);

        for(int i = 0; i<ny; i--){
            for (int j = 0; j < nz; j++) {
                int inovo=ny-1-i;
                linha[j].r=v[dim][inovo][j].r;
                linha[j].g=v[dim][inovo][j].g;
                linha[j].b=v[dim][inovo][j].b;
                linha[j].a=v[dim][inovo][j].a;
                linha[j].isOn=v[dim][inovo][j].isOn;
            }

            matriz.push_back(linha);
        }
   break;
    }

    linha.clear();
    return matriz;
}
