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
//  CLASS ValenceViewer - IMPLEMENTATION
//
//=============================================================================


//== INCLUDES =================================================================

#include "ValenceViewer.h"
#include <vector>
#include <float.h>
#include <limits>

//== IMPLEMENTATION ========================================================== 

ValenceViewer::ValenceViewer(const char* _title, int _width, int _height): MeshViewer(_title, _width, _height) { 
  mesh_.request_vertex_colors();
  add_draw_mode("Vertex Valences");
}


//-----------------------------------------------------------------------------

ValenceViewer::~ValenceViewer() {}

//-----------------------------------------------------------------------------

bool ValenceViewer::open_mesh(const char* _filename) {
    // load mesh
    if (MeshViewer::open_mesh(_filename)) {
        // compute vertex valence and color coding
        calc_valences();
        color_coding();

        glutPostRedisplay();
        return true;
    }
    return false;
}


//-----------------------------------------------------------------------------


void ValenceViewer::calc_valences() {
    // ASSIGNMMENT 2.1 ////////////////////////////////////////////////////////
    // Compute valence of every vertex of "mesh_" and store them in each vertex
    // using for example custom attributes via dynamic customization
    // (hint: use the Mesh::VertexIter iterator)

    // Implement something here
    /////////////////////////////////////////////////////////////////////////////
}


//-----------------------------------------------------------------------------


void ValenceViewer::color_coding() {
    Mesh::Color colors[5] = {{128,187,79},
                             {196,175,48},
                             {229,165,57},
                             {240,128,54},
                             {247,119,70}};
    
    // ASSIGNMMENT 2.2 ///////////////////////////////////////////////////////////
    // Implement a color visualization of your choice that shows the valence of
    // veach ertex of "mesh_". 
    // (hint: use Mesh::Color color type)

    // Implement something here
    /////////////////////////////////////////////////////////////////////////////
}


//-----------------------------------------------------------------------------


void ValenceViewer::draw(const std::string& _draw_mode) {
    if (indices_.empty()) {
        MeshViewer::draw(_draw_mode);
        return;
    }

    if (_draw_mode == "Vertex Valences") {
        glDisable(GL_LIGHTING);
        glShadeModel(GL_SMOOTH);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        GL::glVertexPointer(mesh_.points());
        GL::glNormalPointer(mesh_.vertex_normals());
        GL::glColorPointer(mesh_.vertex_colors());

        glDepthRange(0.01, 1.0);

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT, &indices_[0]);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

        glColor3f(0.1f, 0.1f, 0.1f);
        glEnableClientState(GL_VERTEX_ARRAY);

        GL::glVertexPointer(mesh_.points());
        glDrawBuffer(GL_BACK);
        glDepthRange(0.0, 1.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDepthFunc(GL_LEQUAL);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT, &indices_[0]);
        glDisableClientState(GL_VERTEX_ARRAY);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDepthFunc(GL_LESS);
    }
    else {
        MeshViewer::draw(_draw_mode);
    }
}


//=============================================================================
