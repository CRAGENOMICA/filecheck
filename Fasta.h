/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CFastaStats.h
 * Author: jjene
 *
 * Created on 23 de junio de 2017, 9:51
 */

#ifndef FASTA_H
#define FASTA_H

#include <string>
#include "File.h"

class Fasta : public File {
public:
    Fasta() {}
    Fasta(const std::string & file_name, const std::string & allowed_bases);
    virtual ~Fasta();
    
private:
    bool getSequenceInfo(long int &seq_length, int & seq_lines, long int & read_bytes, char & c);

public:    
    void check(void);
};

#endif /* FASTA_H */

