import py7zr
import os
import re
import pandas as pd
from io import StringIO

def read7Zip(file_path):
    '''
    Input: File path to a 7zip file.
    Returns: a pandas data frame.
    '''
    if not os.path.exists(file_path):
        raise RuntimeError('File does not exist: ' + file_path)

    filter_pattern = re.compile(r'\w+.csv$')
    with py7zr.SevenZipFile(file_path, 'r') as archive:
        allfiles = archive.getnames()
        selected_files = [f for f in allfiles if filter_pattern.match(f)]
        if len(selected_files) != 1:
            raise RuntimeError('Expected 1 CSV file')

        for _, bio in archive.read(selected_files).items():
            csvFile = StringIO(bio.read().decode())
            df = pd.read_csv(csvFile)
            return df
