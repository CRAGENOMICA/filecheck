/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File.cpp
 * Author: jjene
 * 
 * Created on 23 de junio de 2017, 15:03
 */

#include "File.h"

#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "CProgress.h"
#include "zutil.h"

File::File() {
  file_name_ = "";
  allowed_bases_ = "";
  file_size_ = 0;
  first_seq_length_ = 0;
  different_bases_ = "";
  extra_bases_ = "";
  num_sequences_ = 0;
  read_lines_ = 0;
  
  file_handle_ = NULL;
}

File::File(const std::string & file_name, const std::string & allowed_bases) {
  file_name_ = file_name;
  allowed_bases_ = allowed_bases;
  file_size_ = 0;
  first_seq_length_ = 0;
  different_bases_ = "";
  extra_bases_ = "";
  num_sequences_ = 0;
  read_lines_ = 0;

  file_handle_ = NULL;
}

File::File(const File& orig) {
  file_name_ = orig.file_name_;
  allowed_bases_ = orig.allowed_bases_;
  file_size_ = orig.file_size_;
  first_seq_length_ = orig.first_seq_length_;
  different_bases_ = orig.different_bases_;
  extra_bases_ = orig.extra_bases_;
  num_sequences_ = orig.num_sequences_;
  num_sequences_ = orig.num_sequences_;
  read_lines_ = orig.read_lines_;

  file_handle_ = NULL;
}

File::~File() {
  if (file_handle_ != NULL) {
    closeFile();
  }
  
}

long int File::getFileSize(const std::string & file_name) {
  std::ifstream f(file_name.c_str(), std::ios::binary | std::ios::ate);
  long int ret = f.tellg();
  f.close();
  
  return ret;  
}

bool File::discardLine(long int & count) {
  bool eof = false;  
  char c;  
  
  while (((c = getFileChar()) != 0) && (c!='\n')) { count++; }  
  
  if (c != '\n') {
    eof = true;
  } else {
    count++; // count the \n
  }
  
  return eof;
}

std::string File::translateBases(const std::string & bases) {
  std::string ret;
  
  if (bases != "") {
    int c = 0;

    for (unsigned int i=0; i < bases.length(); i++) {
      if (i != 0) {
        ret += ",";
      }
      ret += bases[i];
    }

    ret += ". ASCII codes: (";

    for (unsigned int i=0; i < bases.length(); i++) {
      if (i != 0) {
        ret += ",";
      }
      c = bases[i];
      ret += std::to_string(c);
    }
    ret += ")";
  }
  else {
    ret = "None";
  }  
  return ret;
}

void File::startCheck(const std::string & message) {
  std::cout << "Messages:" << std::endl;
  
  file_size_ = File::getFileSize(this->file_name_);
  
  progress_.set_task(message);
  progress_.set_total(file_size_);
  progress_.Start(); 
  
  openFile();
}

void File::endCheck(void) {
  closeFile();
  
  progress_.Done();

  if (progress_.current() < file_size_) {
    std::cout << "\tError: EOF character found before the real end of file." << std::endl;
  }
  
  std::cout << std::endl;
  std::cout << "Summary:" << std::endl;
  std::cout << std::endl;
  std::cout << "\tFile Name               : " << file_name_ << std::endl;
  std::cout << "\tFile Size               : " << file_size_ << " bytes" << std::endl;
  std::cout << "\tRead Bytes              : " << progress_.percent() << "%" << std::endl; //progress_.current() << " bytes (" 
  std::cout << "\tRead Sequences          : " << num_sequences_ << std::endl;
  std::cout << "\tRead Lines              : " << read_lines_ << std::endl;
  std::cout << "\tSequence Length         : " << first_seq_length_ << " bytes (the first one)" << std::endl;
  std::cout << "\tAllowed Bases Found     : " << File::translateBases(different_bases_) << std::endl;
  std::cout << "\tNot Allowed Bases Found : " << File::translateBases(extra_bases_) << std::endl;
  std::cout << std::endl;
}

bool File::openFile(void) {
  bool ret = true;

  if ((file_handle_ = fzopen(file_name_.c_str(), "r", &gz_)) == NULL) {
    ret = false;
  }
  
  return ret;
}

void File::closeFile(void) {
  fzclose(file_handle_, &gz_);
}

char File::getFileChar(void) {
  return fzgetc(file_handle_, &gz_);  
}

void File::annotateBase(char c) {
  std::string the_char = " ";
  the_char[0] = c;
    
  // Is this base allowed?
  if (allowed_bases_.find(the_char) == std::string::npos) {
    // Base is NOT allowed
    if (extra_bases_.find(the_char) == std::string::npos) {
      // Annotate new NOT allowed base found:
      extra_bases_ += the_char;
    }             
  } else {
    // Base is allowed
    if (different_bases_.find(the_char) == std::string::npos) {
      // Annotate new allowed base found:
      different_bases_ += the_char;
    }             
  }
}
  