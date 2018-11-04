#pragma once

#include <stdio.h>
#include <string.h>

typedef union {
  unsigned short num;
  char bytes[2];
} EndianUnion;

typedef struct {
  unsigned short buletin : 1;
  unsigned short certificat_casatorie : 1;
  unsigned short diploma_licenta : 1;
  unsigned short diploma_master : 1;
  unsigned short diploma_doctor : 1;
  unsigned short fisa_lichidare : 1;
  unsigned short certificate_copii : 1;
} DocumentePrezenteShort;

typedef struct {
  char buletin : 1;
  char certificat_casatorie : 1;
  char diploma_licenta : 1;
  char diploma_master : 1;
  char diploma_doctor : 1;
  char fisa_lichidare : 1;
  char certificate_copii : 1;
} DocumentePrezenteChar;

