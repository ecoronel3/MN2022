import sys
import numpy as np
import reader

def main():
    df = reader.read7Zip('data/train.7z')
    targets = df['label'].to_numpy()
    image = df[1: -1].to_numpy()
    

if __name__ == '__main__':
    main()
    