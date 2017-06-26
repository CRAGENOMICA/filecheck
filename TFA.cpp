/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CTFAStats.cpp
 * Author: jjene
 * 
 * Created on 23 de junio de 2017, 9:51
 */
#include <string>
#include <iostream>
#include <fstream>

#include "TFA.h"
#include "File.h"

#include <fstream>
#include <string>
#include <iostream>
#include <math.h>
#include "CProgress.h"

TFA::TFA(const std::string & file_name, const std::string & allowed_bases) : File(file_name, allowed_bases) {
}

TFA::~TFA() {
}

bool TFA::getSequenceInfo(long int &seq_length, long int & read_bytes) {
  bool eof = false;  
  bool seq_id = true;
  char c;
  
  seq_length = 0;
  
  while ((!eof) && (c != '\n')) { 
    
    if ((c = getFileChar()) <= 0) {
      eof = true;
    }
    else {   
      read_bytes++;
      
      if (c == '\t') {
        seq_id = false;
      }
      else {
        if (c != '\n') {
          if (seq_id == false) {
            seq_length++;

            annotateBase(c);
          }
        }
      }
    }
  }
  
  return eof;
}

void TFA::check(void) {

  std::cout << std::endl << "Checking TFA File..." << std::endl << std::endl;
  
  File::startCheck("\tChecking TFA File");
  
  long int seq_length = 0;
  
  std::string prev_different_bases = allowed_bases_;
  
  read_lines_ = 0;
  int read_sequences = 0;
  long int read_bytes = 0;
  
  first_seq_length_ = 0;
  
  
  bool eof = false;
  char c;
  while (!eof) {
    
    if ((c = getFileChar()) <= 0) {
      eof = true;
    } else {
      read_bytes++;
      
      if (c == '#') {
        eof = discardLine(read_bytes);
        read_lines_++;
      } else {
        prev_different_bases = extra_bases_;
        eof = getSequenceInfo(seq_length, read_bytes);
        if (seq_length > 0) {
          num_sequences_++;
        }
        read_lines_++;

        if (read_sequences == 0) {
          first_seq_length_ = seq_length;
        }
        
        if (prev_different_bases != extra_bases_) {
          std::cout << "\r" << "\tError: Ln: " << read_lines_ << ". Seq: " << read_sequences << ". New not allowed base found. List of not allowed bases found until now: " << File::translateBases(extra_bases_) << std::endl << std::flush;
          progress_.Show();
        }

        if (seq_length != first_seq_length_) {
          std::cout << "\r" << "\tError: Ln: " << read_lines_ << ". Seq: " << read_sequences << ". It has " << seq_length << " bases. It differs of " << (first_seq_length_ - seq_length) << " bases from the first sequence." << std::endl << std::flush;
          progress_.Show();
        }

        read_sequences++;

      }

      progress_.MoveOn(read_bytes);
      read_bytes = 0;
    }
  }
  
  File::endCheck();
}

