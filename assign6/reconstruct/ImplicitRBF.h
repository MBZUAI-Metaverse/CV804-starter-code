//=============================================================================
//                                                
//   Code framework for the lecture
//
//   "CV804: 3D Geometry Processing"
//
//   Lecturer: Hao Li
//   TAs: Phong Tran, Long Nhat Ho
//
//   Modified from
//   "Surface Representation and Geometric Modeling"
//   by Mark Pauly, Mario Botsch, Balint Miklos, and Hao Li
//
//   Copyright (C) 2007 by  Applied Geometry Group and 
//                          Computer Graphics Laboratory, ETH Zurich
//                                                                         
//-----------------------------------------------------------------------------
//                                                                            
//                                License                                     
//                                                                            
//   This program is free software; you can redistribute it and/or
//   modify it under the terms of the GNU General Public License
//   as published by the Free Software Foundation; either version 2
//   of the License, or (at your option) any later version.
//   
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//   
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin Street, Fifth Floor, 
//   Boston, MA  02110-1301, USA.
//                                                                            
//=============================================================================
//=============================================================================
//
//  CLASS ImplicitRBF
//
//=============================================================================

#ifndef RBF_HH
#define RBF_HH

//=============================================================================

#include <OpenMesh/Core/Geometry/VectorT.hh>
#include <vector>
#include <gmm.h>

//=============================================================================

class ImplicitRBF
{
public:

    typedef OpenMesh::Vec3f            Vec3f;
    typedef OpenMesh::Vec3d            Vec3d;
    typedef gmm::dense_matrix<double>  gmmMatrix;
    typedef std::vector<double>        gmmVector;

    
    // fit RBF to given constraints
    virtual ~ImplicitRBF(){}
    ImplicitRBF( 
        const std::vector<Vec3f>& _points, 
        const std::vector<Vec3f>& _normals );

    // evaluate RBF at position _p
    double operator()(const Vec3f& _p) const;

private:

    // evaluate basis function of RBF
    static double kernel(const Vec3d& _c, const Vec3d& _x)
    {
        double r = (_x-_c).norm();
        return r*r*r;
    }

    // solve linear system _A * _x = _b
    void solve_linear_system( 
        gmmMatrix& _A, 
        gmmVector& _b, 
        gmmVector& _x );
  
private:

    std::vector<Vec3d>   centers_;
    std::vector<double>  weights_;
};

//=============================================================================
#endif // RBF_HH defined
//=============================================================================
