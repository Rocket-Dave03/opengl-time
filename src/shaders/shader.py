#!/usr/bin/env python3

import sys
import os

input_file = sys.argv[1]
output_file = sys.argv[2]

inp_name = os.path.basename(input_file)

with open(output_file, 'w+') as out:
    with open(input_file) as inp:
        out.write(f"const char *SHADER_{inp_name.upper().replace('.','_')} = \n")
        lines = inp.readlines()
        if len(lines) == 0:
            out.write('\t""')
        else:
            for line in lines:
                line = line.replace('\n', '\\n')
                out.write(f'\t"{line}"\n')
        out.write(';')

