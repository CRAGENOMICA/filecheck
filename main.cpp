/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jjene
 *
 * Created on 23 de junio de 2017, 12:10
 */


// "${OUTPUT_PATH}" /data/example_files/sara/new/chrom_14.imputed_without_low_R2.All_pigs_ERROR.tfa
// "${OUTPUT_PATH}" /data/file.fa
  
#include "Fasta.h"
#include "TFA.h"

#include <iostream>
#include <string>

using namespace std;

#define APP_NAME    "FileCheck"
#define CMD_NAME    "filecheck"
#define APP_VERSION "23/June/2017"

void help(void) {
  std::cout << APP_NAME << " " << APP_VERSION << std::endl;
  std::cout << "The application checks Fasta files and T-Fasta files. It uses the file name extension to recognize the file type." << std::endl;
  std::cout << std::endl;
  std::cout << "Syntax  : " << CMD_NAME << " <File Name> \"<Allowed Bases>\"" << std::endl;
  std::cout << std::endl;
  std::cout << "Example : " << CMD_NAME << " file.tfa.gz \"ATCGN\"" << std::endl;
  std::cout << std::endl;
}

/*
 * 
 */
int main(int argc, char** argv) {
  if (argc != 3) {
    help();
  } else {
    std::string file_name = argv[1];
    std::string allowed_bases = argv[2];
    if(file_name.find(".fa") != std::string::npos) {
      // FASTA
      Fasta fasta(file_name, allowed_bases);
      fasta.check();
    }
    if(file_name.find(".tfa") != std::string::npos) {
      // T-FASTA
      TFA tfasta(file_name, allowed_bases);
      tfasta.check();
    }
  }

  return 0;
}

