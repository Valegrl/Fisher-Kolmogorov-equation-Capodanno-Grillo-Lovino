#ifndef PARAMETER_READER_HPP
#define PARAMETER_READER_HPP

#include <deal.II/base/parameter_handler.h>
#include <deal.II/base/subscriptor.h>
#include <deal.II/numerics/data_out.h>
#include <string>

using namespace dealii;

/**
 * Class to read and manage program parameters from a parameter file.
 */
class ParameterReader : public Subscriptor
{
public:
  /**
   * Constructor.
   * @param paramhandler Reference to a ParameterHandler object
   */
  ParameterReader(ParameterHandler &paramhandler);
  
  /**
   * Read parameters from a file.
   * @param parameter_file Path to the parameter file
   */
  void read_parameters(const std::string &parameter_file);
 
private:
  /**
   * Declare all parameters that can be specified in the parameter file.
   */
  void declare_parameters();
  
  /**
   * Reference to the parameter handler that will manage the parameters.
   */
  ParameterHandler &prm;
};

ParameterReader::ParameterReader(ParameterHandler &paramhandler)
  : prm(paramhandler)
{}

void ParameterReader::declare_parameters()
{
  prm.enter_subsection("Mesh & geometry parameters");
  {                   
    //prm.declare_entry("Mesh file",
    //                  "../mesh/brain-h3.0.msh",
    //                  Patterns::Anything(),
    //                  "Path to the mesh file");
    prm.declare_entry("Degree",
                      "1",
                      Patterns::Integer(1),
                      "Polynomial degree of finite element");
  }
  prm.leave_subsection();

  prm.enter_subsection("Physical constants");
  {
    prm.declare_entry("Dext", 
                      "1.0", 
                      Patterns::Double(0),
                      "Dext coefficient for diffusion term");
    prm.declare_entry("Daxn",
                      "10.0", 
                      Patterns::Double(0),
                      "Daxn coefficient for diffusion term");
    prm.declare_entry("Alpha coefficient", 
                      "0.1", 
                      Patterns::Double(0),
                      "Alpha coefficient for reaction term");
  }
  prm.leave_subsection();

  prm.enter_subsection("Time stepping parameters");
  {
    prm.declare_entry("T", 
                      "1.0", 
                      Patterns::Double(0),
                      "Final simulation time");
                      
    prm.declare_entry("deltat", 
                      "0.1", 
                      Patterns::Double(0),
                      "Time step size");
                      
    prm.declare_entry("Theta", 
                      "1.0", 
                      Patterns::Double(0.0, 1.0),
                      "Theta value for the time-stepping method (0=explicit, 1=implicit)");
  }
  prm.leave_subsection();
  
  prm.enter_subsection("Solver parameters");
  {
    prm.declare_entry("Max Newton iterations", 
                      "1000", 
                      Patterns::Integer(1),
                      "Maximum number of Newton iterations");
                      
    prm.declare_entry("Newton tolerance", 
                      "1e-6", 
                      Patterns::Double(0),
                      "Tolerance for Newton iterations");
                      
    prm.declare_entry("Max CG iterations", 
                      "1000", 
                      Patterns::Integer(1),
                      "Maximum number of CG iterations");
                      
    prm.declare_entry("CG tolerance factor", 
                      "1e-6", 
                      Patterns::Double(0),
                      "Tolerance factor for CG solver (multiplied by residual norm)");
  }
  prm.leave_subsection();

}

void ParameterReader::read_parameters(const std::string &parameter_file)
{
  declare_parameters();
  prm.parse_input(parameter_file);
}

#endif // PARAMETER_READER_HPP