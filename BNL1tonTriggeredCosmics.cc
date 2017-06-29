/*
  This program compiles against the CRY cosmic ray generator 
  (https://nuclear.llnl.gov/simulation/main.html). It generates
  cosmic muons and filters them according to whether or not they
  pass through the scintillator paddles placed above the BNL
  1 ton tank.
*/
  

#include "CRYGenerator.h"
#include "CRYSetup.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>  // For Ubuntu Linux

#include <math.h>

struct scint_strip{
      double z_center;
      double x_max;
      double x_min;
      double y_max;
      double y_min;
  };
int main( int argc, const char *argv[]) {

  int nEv=500; // Number of cosmic ray events PER FILE
  //int nFiles=2; // Number of files to generate
  //std::string outFilePath = "/storage/shared/junjiejiang/BNL1ton_cosmic_mu/002/CRY/cosmic_mu_data/CosmicMuon";
  //std::string outFilePath = "/storage/shared/junjiejiang/BNL1ton_cosmic_mu/CRY/cosmic_mu_data/CosmicMuon";
  double cm = 10.0;
  double m = 1000.0;
  double zOffset = 3.0*m; // Simulate events with z = 2.0 m
  
  
std::vector<scint_strip > scint_info(4);
  //unit mm
  
  (scint_info.at(0)).z_center=(163.35375-50.0)*cm;
  (scint_info.at(0)).x_max=(26.67+5.08)*cm;
  (scint_info.at(0)).x_min=(26.67-5.08)*cm;
  (scint_info.at(0)).y_max=(2.441575+4.445)*cm;
  (scint_info.at(0)).y_min=(2.441575-4.445)*cm;

  (scint_info.at(1)).z_center=(138.97006-50.0)*cm;
  (scint_info.at(1)).x_max=(26.705+5.08)*cm;
  (scint_info.at(1)).x_min=(26.705-5.08)*cm;
  (scint_info.at(1)).y_max=(2.447925+5.715)*cm;
  (scint_info.at(1)).y_min=(2.447925-5.715)*cm;

  (scint_info.at(2)).z_center=(164.465-50.0)*cm;
  (scint_info.at(2)).x_max=(31.90875+5.08)*cm;
  (scint_info.at(2)).x_min=(31.90875-5.08)*cm;
  (scint_info.at(2)).y_max=(2.619375+5.08)*cm;
  (scint_info.at(2)).y_min=(2.619375-5.08)*cm;

  (scint_info.at(3)).z_center=(139.65435-50.0)*cm;
  (scint_info.at(3)).x_max=(27.305+5.08)*cm;
  (scint_info.at(3)).x_min=(27.305-5.08)*cm;
  (scint_info.at(3)).y_max=(9.426575+5.715)*cm;
  (scint_info.at(3)).y_min=(9.426575-5.715)*cm;

  /*(scint_info.at(4)).z_center=;
  (scint_info.at(4)).x_max=;
  (scint_info.at(4)).x_min=;
  (scint_info.at(4)).y_max=;
  (scint_info.at(4)).y_min=;

  (scint_info.at(5)).z_center=;
  (scint_info.at(5)).x_max=;
  (scint_info.at(5)).x_min=;
  (scint_info.at(5)).y_max=;
  (scint_info.at(5)).y_min=;*/

  if ( argc < 5 ) {
    std::cout << "usage " << argv[0] << " <setup file name> <N files> <N events per file> <Output file base name>\n";
    std::cout << "N events = " << nEv << " by default\n";
    return 0;
  }

  nEv=atoi(argv[3]);
  int nFiles = atoi(argv[2]);
  
  //  int file = 2;
     
  // Read the setup file into setupString
  std::ifstream inputFile;
  inputFile.open(argv[1],std::ios::in);
  char buffer[1000];

  std::string setupString("");
  while ( !inputFile.getline(buffer,1000).eof()) {
    setupString.append(buffer);
    setupString.append(" ");
  }

  // Parse the contents of the setup file
  CRYSetup *setup=new CRYSetup(setupString,"./data");

  // Setup the CRY event generator
  CRYGenerator gen(setup);

  // Generate the events

  //int file = n;
  for (int file = 0; file < nFiles; file++){

    std::ofstream outFile;
    char outFileName[1000];
    sprintf(outFileName, "%s_%i.dat", argv[4], file );
    outFile.open(outFileName);

    
  //  std::cout << "File " << file << std::endl;
    
    // Open output file
   


    
    std::vector<CRYParticle*> *ev=new std::vector<CRYParticle*>;
    for ( int i=0; i<nEv; i++) {
      int HowManyPass = 0;
      while (HowManyPass==0){
      ev->clear();
      gen.genEvent(ev);
      std::vector<bool> PassNum;
      for (unsigned k=0;k<ev->size();k++){
          CRYParticle* p_test = (*ev)[k];
          double velocity_x = p_test->u();
          double velocity_y = p_test->v();
          double velocity_z = p_test->w();
          double pos_x = p_test->x()*m;
          double pos_y = p_test->y()*m;
          double pos_z = p_test->z()*m+zOffset;

          bool PassH0 = false;
          bool PassH1 = false;
          bool PassH2 = false;
          bool PassH3 = false;
          
          bool temp = false;
          double linear_para;
          double temp_x,temp_y;
          //check H0,H2
          //check H0
          linear_para = ((scint_info.at(0)).z_center-pos_z)/velocity_z;
          temp_x = pos_x + linear_para*velocity_x;
          temp_y = pos_y + linear_para*velocity_y;
          if((temp_x<=(scint_info.at(0)).x_max)&&(temp_x>=(scint_info.at(0)).x_min)&&(temp_y<=(scint_info.at(0)).y_max)&&(temp_y>=(scint_info.at(0)).y_min))
              PassH0 = true;
         //check H2
          linear_para = ((scint_info.at(2)).z_center-pos_z)/velocity_z;
          temp_x = pos_x + linear_para*velocity_x;
          temp_y = pos_y + linear_para*velocity_y;
          if((temp_x<=(scint_info.at(2)).x_max)&&(temp_x>=(scint_info.at(2)).x_min)&&(temp_y<=(scint_info.at(2)).y_max)&&(temp_y>=(scint_info.at(2)).y_min))
              PassH2 = true;
        
          if (!(PassH0||PassH2)){
              PassNum.push_back(temp);
              continue;
          }

          //check H1,H3
          //check H1
          linear_para = ((scint_info.at(1)).z_center-pos_z)/velocity_z;
          temp_x = pos_x + linear_para*velocity_x;
          temp_y = pos_y + linear_para*velocity_y;
          if((temp_x<=(scint_info.at(1)).x_max)&&(temp_x>=(scint_info.at(1)).x_min)&&(temp_y<=(scint_info.at(1)).y_max)&&(temp_y>=(scint_info.at(1)).y_min))
              PassH1 = true;
          //check H3
          linear_para = ((scint_info.at(3)).z_center-pos_z)/velocity_z;
          temp_x = pos_x + linear_para*velocity_x;
          temp_y = pos_y + linear_para*velocity_y;
          if((temp_x<=(scint_info.at(3)).x_max)&&(temp_x>=(scint_info.at(3)).x_min)&&(temp_y<=(scint_info.at(3)).y_max)&&(temp_y>=(scint_info.at(3)).y_min))
              PassH3 = true;
          if (!(PassH1||PassH3)){
              PassNum.push_back(temp);
              continue;
          }
          else{
              temp = true;
              HowManyPass++;
              PassNum.push_back(temp);
          }
      }
      if (HowManyPass==0)
	continue;
      // RAT format:
      outFile << HowManyPass << std::endl;

      // Write the event information to standard output
      std::cout << "Event: " << i << std::endl;

      double prevT = 0.;
    
      for ( unsigned j=0; j<ev->size(); j++) {
        if (!(PassNum.at(j)))
        continue;
        
        CRYParticle* p = (*ev)[j];

        // Status: 1 is generator final state
        int ISTHEP = 1;

        // PDG code
        int IDHEP = p->PDGid();

        // First and second daughters, set to 0 if particle not decayed
        int JDAHEP1 = 0;
        int JDAHEP2 = 0;

        // Momentum in GeV
        double ke = p->ke()/1e3;
        double mass = 0.1057;
        double mom = sqrt( pow(ke+mass, 2) - pow(mass, 2) );
      
        double PHEP1 = p->u() * mom;
        double PHEP2 = p->v() * mom;
        double PHEP3 = p->w() * mom;

        // Mass in GeV (optional, but I don't know how to skip it)
        double PHEP5 = mass;

        // vertex _delta_ time, in ns. DT is a relative shift from the previous line
        double DT;
        if (prevT <= 1e-10) {
          DT = 0.;
        } else {
          DT = (p->t() - prevT)*1e9; // s -> ns
        }
        std::cout << "THIS TIME " << p->t() << " PREVIOUS TIME " << prevT << std::endl;
        prevT = p->t();
        
        // Position
        double X = p->x()*m; // m -> mm
        double Y = p->y()*m; // m -> mm
        double Z = p->z()*m+zOffset; // m -> mm
        
        //        outFile << "\t";
        outFile << ISTHEP << " ";
        outFile << IDHEP << " ";
        outFile << JDAHEP1 << " ";
        outFile << JDAHEP2 << " ";
        outFile << PHEP1 << " ";
        outFile << PHEP2 << " ";
        outFile << PHEP3 << " ";
        outFile << PHEP5 << " ";
        outFile << DT << " ";
        outFile << X << " ";
        outFile << Y << " ";
        outFile << Z;
        outFile << std::endl;
        
        delete (*ev)[j];
      }
    }
    }
    outFile.close();
     }
  
  std::cout << "Run completed.\n";
  std::cout << "Total time simulated: " << gen.timeSimulated() << " seconds\n";
  return 0;
}
