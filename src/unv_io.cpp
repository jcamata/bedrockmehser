
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;





void UNVIO_WriteNodes(std::ofstream &out_file, int n_nodes, vector<double> &coords)
{
    int _nodes_dataset_label = 2411;
    // Write beginning of dataset
    out_file << "    -1\n"
             << "  "
             << _nodes_dataset_label
             << '\n';
     unsigned int
        exp_coord_sys_dummy  = 0, // export coordinate sys. (not supported yet)
        disp_coord_sys_dummy = 0, // displacement coordinate sys. (not supp. yet)
        color_dummy          = 0; // color(not supported yet)
  
     // Use scientific notation with captial E and 16 digits for printing out the coordinates
    out_file << std::scientific << std::setprecision(16) << std::uppercase;
    
    for(int inode = 0; inode < n_nodes; ++inode)
    {
        out_file << std::setw(10) << inode
                 << std::setw(10) << exp_coord_sys_dummy
                 << std::setw(10) << disp_coord_sys_dummy
                 << std::setw(10) << color_dummy
                 << '\n';
        out_file << std::setw(25) << coords[inode*3+0]
                 << std::setw(25) << coords[inode*3+1]
                 << std::setw(25) << coords[inode*3+2]
                 << '\n';
    }
    // Write end of dataset
    out_file << "    -1\n";
}

void UNVIO_WriteElements(std::ofstream &out_file, int n_elements, vector<int> &conn, vector<int> &tag)
{
    int  _elements_dataset_label = 2467;
    // Write beginning of dataset
    out_file << "    -1\n"
             << "  "
             << _elements_dataset_label
             << "\n";
     unsigned
        fe_descriptor_id    = 0,    // FE descriptor id
        phys_prop_tab_dummy = 2, // physical property (not supported yet)
        mat_prop_tab_dummy  = 1,  // material property 
        color_dummy         = 7;         // color (not supported yet)
     
     unsigned int assign_elem_nodes[8];
     fe_descriptor_id = 115; // Solid Linear Brick
     assign_elem_nodes[0] = 0;
     assign_elem_nodes[1] = 4;
     assign_elem_nodes[2] = 5;
     assign_elem_nodes[3] = 1;
     assign_elem_nodes[4] = 3;
     assign_elem_nodes[5] = 7;
     assign_elem_nodes[6] = 6;
     assign_elem_nodes[7] = 2;
     
     for(int  iel = 0; iel < n_elements; ++iel)
     {
          out_file << std::setw(10)   << iel            // element ID
                << std::setw(10) << fe_descriptor_id    // type of element
                << std::setw(10) << phys_prop_tab_dummy // not supported
                << std::setw(10) << tag[iel]            // not supported
                << std::setw(10) << color_dummy         // not supported
                << std::setw(10) << 8                   // No. of nodes per element
                << '\n';
          
          for(int j =0; j < 8; j++)
          {
              
              int node_id = conn[iel*8+assign_elem_nodes[j]];
              out_file << std::setw(10) << node_id;
          }
          out_file << '\n';
     }
     // Write end of dataset
    out_file << "    -1\n";
}

void WriteMeshUNV(int n_total_nodes,int n_total_elements, 
                  std::vector<double> coords,
                  std::vector<int>  elements,
                  std::vector<int> element_tag, 
                  const char* filename)
{

	std::ofstream out_file (filename);
        if(! out_file.good())
	{
            cerr << "ERROR: output file not good" << endl;
            return;
	}
        
       UNVIO_WriteNodes(out_file,n_total_nodes, coords);
       UNVIO_WriteElements(out_file,n_total_elements,elements, element_tag);
       out_file.close();
       
}
