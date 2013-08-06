#include <vtkSmoothPolyDataFilter.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>


int main(int argc, char *argv[])
{
	int nbPointsInput, nbPointsOutput; 

	// INPUT MESH \\

	vtkSmartPointer<vtkPolyDataReader> reader=vtkSmartPointer<vtkPolyDataReader>::New(); 
	reader->SetFileName(argv[1]);
	reader->Update();
	nbPointsInput=(reader->GetOutput())->GetNumberOfPoints(); 
	std::cout<<nbPointsInput<<std::endl; 	


	// SMOOTING \\

	vtkSmartPointer <vtkSmoothPolyDataFilter> smoothFilter =
	vtkSmartPointer <vtkSmoothPolyDataFilter> ::New(); 
	smoothFilter -> SetInput(reader->GetOutput());
	smoothFilter -> SetRelaxationFactor(atof(argv[3])); 


	// OUTPUT MESH \\ 
	
	vtkSmartPointer <vtkPolyDataWriter> writer = vtkSmartPointer <vtkPolyDataWriter> ::New(); 
	writer -> SetInput(smoothFilter -> GetOutput()); 
	writer -> SetFileName(argv[2]);
	writer -> Update();
	nbPointsOutput = (smoothFilter->GetOutput()) -> GetNumberOfPoints(); 
	std::cout << nbPointsOutput << std::endl; 


	// DISPLAY \\

	//BOTH MESH
	//Render Window
	vtkSmartPointer <vtkRenderWindow> renderWindow =
	vtkSmartPointer <vtkRenderWindow> :: New(); 
 	renderWindow -> SetSize(600,300);
	//Interactor
	vtkSmartPointer <vtkRenderWindowInteractor> renderWindowInteractor =
	vtkSmartPointer <vtkRenderWindowInteractor> :: New(); 
	renderWindowInteractor -> SetRenderWindow(renderWindow); 
	
	//INPUT MESH 
	//Mapper
	vtkSmartPointer <vtkPolyDataMapper> inputMapper = 
	vtkSmartPointer <vtkPolyDataMapper> :: New(); 
	inputMapper -> SetInputConnection(reader -> GetOutputPort()); 	
	//Actor
	vtkSmartPointer <vtkActor> inputActor =
	vtkSmartPointer <vtkActor> :: New(); 
	inputActor -> SetMapper(inputMapper); 
	//Renderer
	vtkSmartPointer <vtkRenderer> leftRenderer = 
	vtkSmartPointer <vtkRenderer> :: New();
	double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
	renderWindow -> AddRenderer (leftRenderer); 
	leftRenderer -> SetViewport (leftViewport); 
	leftRenderer -> SetBackground (0.6,0.5,0.4);
	leftRenderer -> AddActor(inputActor);
	leftRenderer -> ResetCamera(); 

	//OUPUT MESH
	//Mapper
	vtkSmartPointer <vtkPolyDataMapper> outputMapper = 
	vtkSmartPointer <vtkPolyDataMapper> :: New(); 
	outputMapper -> SetInputConnection(smoothFilter-> GetOutputPort()); 
	//Actor
	vtkSmartPointer <vtkActor> outputActor =
	vtkSmartPointer <vtkActor> :: New(); 
	outputActor -> SetMapper(outputMapper); 
	//Renderer
	vtkSmartPointer <vtkRenderer> rightRenderer = 
	vtkSmartPointer <vtkRenderer> :: New();
	double rightViewport[4] = {0.5, 0.0, 1.0, 1.0}; 
	renderWindow -> AddRenderer (rightRenderer); 
	rightRenderer -> SetViewport (rightViewport); 
	rightRenderer -> SetBackground (0.4, 0.5, 0.6);
	rightRenderer -> AddActor(outputActor);  
	rightRenderer -> ResetCamera(); 

	//START
	renderWindow -> Render(); 
	renderWindowInteractor -> Start(); 

	return EXIT_SUCCESS; 
}
