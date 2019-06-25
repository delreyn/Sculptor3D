#ifndef SCULPTOR_H
#define SCULPTOR_H

#include <string>
#include <vector>

/**
* @file sculptor.h
* @brief this header file will contain all required
* definitions and basic utilities functions for actually crete the sculptor with voxels.
*
* @author Reyne Jasson
*
* @date 20/06/2019
*/

struct Voxel {
  float r,g,b; // Colors
  float a;
// Transparency
  bool isOn; // Included or not
};

class Sculptor {
protected:
  Voxel ***v;
  // 3D matrix
  int nx,ny,nz; // Dimensions
  float r,g,b,a; // Current drawing color
public:
  Sculptor(int tx,int ty,int tz);
  void setColor(float _r, float _g, float _b, float alpha);
  void putVoxel(int x, int y, int z);
  void cutVoxel(int x, int y, int z);
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  std::vector<std::vector<Voxel>> readMx (int dim, int plane);
  void writeOFF(const std::string filename);
  void writeVECT(const std::string filename);
  ~Sculptor();
};




#endif // SCULPTOR_H
