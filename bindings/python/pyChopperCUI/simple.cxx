include <boost/python.hpp>
 
 
char const* hello(){
  return "hello, world";
}
 
 
BOOST_PYTHON_MODULE( simple ){
   
  boost::python::def( "hello", hello );
 
}