/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CFastaStats.cpp
 * Author: jjene
 * 
 * Created on 23 de junio de 2017, 9:51
 */
#include <string>
#include <iostream>
#include <fstream>

#include "Fasta.h"
#include "File.h"

#include <fstream>
#include <string>
#include <iostream>
#include <math.h>
#include "CProgress.h"

Fasta::Fasta(const std::string & file_name, const std::string & allowed_bases) : File(file_name, allowed_bases) {
}

Fasta::~Fasta() {
}

bool Fasta::getSequenceInfo(long int &seq_length, int & seq_lines, long int & read_bytes, char & c) {
  bool eof = false;  
  bool check_c = false;
  bool end_of_seq = false;
 
  seq_length = 0;
  
  while ((!eof) && (!end_of_seq)) { 

    if ((c = getFileChar()) <= 0) {
      eof = true;
    }
    else {
      read_bytes++;         // count read bytes
      
      if (c != '\n') {   // \n are not count as sequence length
        if ((check_c == true) && ((c == '#') || (c == '>'))) { // start of a new sequence or comment
          end_of_seq = true;
        }
        else {
          seq_length++;

          annotateBase(c);
        }
      } else {
        seq_lines++;     // count lines of the current sequence
        check_c = true;  // check next char for looking for a new sequence start or line comment
      }
    }
  }
  
  return eof;
}

void Fasta::check(void) {
  
  std::cout << std::endl << "Checking Fasta File..." << std::endl << std::endl;
  
  File::startCheck("\tChecking Fasta File");

  
  long int seq_length = 0;
  
  std::string prev_different_bases = allowed_bases_;  
  int seq_lines = 0;
  bool read_char = true;
  read_lines_ = 0;
  int read_sequences = 0;
  long int read_bytes = 0;
  
  first_seq_length_ = 0;
  
  bool eof = false;
  char c;
  while (!eof) {
    
    if (read_char) {
      if ((c = getFileChar()) <= 0) {
        eof = true;
      } else {
        read_bytes++;
      }
    } else {
      read_char = true;
    }
      
    if (c == '#') {
      eof = discardLine(read_bytes);
      read_lines_++;
    } else {
      if (c == '>') {
        eof = discardLine(read_bytes);
        read_lines_++;
      }
      else {
        prev_different_bases = extra_bases_;
        eof = getSequenceInfo(seq_length, seq_lines, read_bytes, c);
        num_sequences_++;
        read_lines_ += seq_lines;
        read_char = false;
        
        if (read_sequences == 0) {
          first_seq_length_ = seq_length;
        }
        
        
        if (prev_different_bases != extra_bases_) {
          std::cout << "\r" << "\tError: Ln: " << read_lines_ << ". Seq: " << read_sequences << ". New not allowed base found. List of not allowed bases found until now: " << File::translateBases(extra_bases_) << std::endl << std::flush;
          progress_.Show();
        }
          
        if (seq_length != first_seq_length_) {
          std::cout << "\r" << "\tError: Ln: " << read_lines_ << ". Seq: " << read_sequences << ". It has " << seq_length << " bases. It differs of " << (first_seq_length_ - seq_length) << " bases from the first sequence." << std::endl;
          progress_.Show();
        }

        read_sequences++;
      }
    }
    
    progress_.MoveOn(read_bytes);
    read_bytes = 0;
  }
  
  File::endCheck();
}


