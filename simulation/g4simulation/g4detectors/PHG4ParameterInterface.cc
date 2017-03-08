#include "PHG4ParameterInterface.h"
#include "PHG4Parameters.h"

#include <phool/PHCompositeNode.h>
#include <phool/PHDataNode.h>

#include <TSystem.h>

using namespace std;

PHG4ParameterInterface::PHG4ParameterInterface(const std::string &name):
params(new PHG4Parameters(name))
{}

PHG4ParameterInterface::~PHG4ParameterInterface()
{
  delete params;
}

void
PHG4ParameterInterface::set_paramname(const string &name)
{
  params->set_name(name);
}

void
PHG4ParameterInterface::set_default_double_param( const std::string &name, const double dval)
{
  if (default_double.find(name) == default_double.end())
    {
      default_double[name] = dval;
    }
  else
    {
      cout << "trying to overwrite default double " << name << " " 
	   << default_double[name] << " with " << dval << endl;
      gSystem->Exit(1);
    }
  return;
}

void
PHG4ParameterInterface::set_default_int_param( const std::string &name, const int ival)
{
  if (default_int.find(name) == default_int.end())
    {
      default_int[name] = ival;
    }
  else
    {
      cout << "trying to overwrite default int " << name << " " 
	   << default_int[name] << " with " << ival << endl;
      gSystem->Exit(1);
    }
  return;
}

void
PHG4ParameterInterface::set_default_string_param( const std::string &name, const string &sval)
{
  if (default_string.find(name) == default_string.end())
    {
      default_string[name] = sval;
    }
  else
    {
      cout << "trying to overwrite default string " << name << " " 
	   << default_string[name] << " with " << sval << endl;
      gSystem->Exit(1);
    }
  return;
}
void
PHG4ParameterInterface::set_double_param(const std::string &name, const double dval)
{
  if (default_double.find(name) == default_double.end())
    {
      cout << "double parameter " << name << " not implemented" << endl;
      cout << "implemented double parameters are:" << endl;
      for (map<const string, double>::const_iterator iter = default_double.begin(); iter != default_double.end(); ++iter)
	{
	  cout << iter->first << endl;
	}
      return;
    }
  dparams[name] = dval;
}

double
PHG4ParameterInterface::get_double_param(const std::string &name) const
{
  return params->get_double_param(name);
}

void
PHG4ParameterInterface::set_int_param(const std::string &name, const int ival)
{
  if (default_int.find(name) == default_int.end())
    {
      cout << "integer parameter " << name << " not implemented" << endl;
      cout << "implemented integer parameters are:" << endl;
      for (map<const string, int>::const_iterator iter = default_int.begin(); iter != default_int.end(); ++iter)
	{
	  cout << iter->first << endl;
	}
      return;
    }
  iparams[name] = ival;
}

int
PHG4ParameterInterface::get_int_param(const std::string &name) const
{
  return params->get_int_param(name);
}

void
PHG4ParameterInterface::set_string_param(const std::string &name, const string &sval)
{
  if (default_string.find(name) == default_string.end())
    {
      cout << "string parameter " << name << " not implemented" << endl;
      cout << "implemented string parameters are:" << endl;
      for (map<const string, string>::const_iterator iter = default_string.begin(); iter != default_string.end(); ++iter)
	{
	  cout << iter->first << endl;
	}
      return;
    }
  cparams[name] = sval;
}

string
PHG4ParameterInterface::get_string_param(const std::string &name) const
{
  return params->get_string_param(name);
}

void
PHG4ParameterInterface::UpdateParametersWithMacro()
{
  for (map<const string,double>::const_iterator iter = dparams.begin(); iter != dparams.end(); ++iter)
    {
      params->set_double_param(iter->first,iter->second);
    }
  for (map<const string,int>::const_iterator iter = iparams.begin(); iter != iparams.end(); ++iter)
    {
      params->set_int_param(iter->first,iter->second);
    }
  for (map<const string,string>::const_iterator iter = cparams.begin(); iter != cparams.end(); ++iter)
    {
      params->set_string_param(iter->first,iter->second);
    }
  return;
}

void
PHG4ParameterInterface::SaveToNodeTree(PHCompositeNode *runNode, const string &nodename)
{
  params->SaveToNodeTree(runNode, nodename);
  return;
}

void
PHG4ParameterInterface::PutOnParNode(PHCompositeNode *parNode, const string &nodename)
{
  parNode->addNode(new PHDataNode<PHG4Parameters>(params,nodename));
}

void
PHG4ParameterInterface::InitializeParameters()
{
  SetDefaultParameters(); // call method from specific subsystem
  // now load those parameters to our params class
  for (map<const string,double>::const_iterator iter = default_double.begin(); iter != default_double.end(); ++iter)
    {
      params->set_double_param(iter->first,iter->second);
    }
  for (map<const string,int>::const_iterator iter = default_int.begin(); iter != default_int.end(); ++iter)
    {
      params->set_int_param(iter->first,iter->second);
    }
  for (map<const string,string>::const_iterator iter = default_string.begin(); iter != default_string.end(); ++iter)
    {
      params->set_string_param(iter->first,iter->second);
    }
}
