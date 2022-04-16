import subprocess as sp
import os
import json
from datetime import datetime

pathToExe = "../../build/Release/BenchmarkEGvsLU.exe"

def process(inputFilesDir, repeat):
    results = []

    for filename in os.listdir(inputFilesDir):
        input_file = os.path.join(inputFilesDir, filename)
        if os.path.isfile(input_file) and input_file.endswith(".in"):
            print("[{0:}] processing {1:}".format(datetime.now().strftime("%Y-%m-%d %H:%M:%S"), filename))
            process = sp.Popen([pathToExe, input_file, str(repeat)], stdout=sp.PIPE)
            (output, err) = process.communicate()
            exitCode = process.wait()
            resultStr = output.decode('utf-8')
            results.append(json.loads(resultStr))

    return results

def main(inputFilesDir, set, repeat = 50):
    now = datetime.now()
    currentTime = now.strftime("%Y%m%d_%H%M%S")
    outputFilename = '../exp/testEGvsLU/results{:}_{:}.json'.format(set, currentTime)
    results = process(inputFilesDir, repeat)
    print("[{0:}] finished.".format(datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
    with open(outputFilename,'w', encoding='utf-8') as outputFile:
        outputFile.write(json.dumps(results, indent=4))

if __name__ == '__main__':
    main(inputFilesDir = '../exp/testEGvsLU/input2/', set=2)
    main(inputFilesDir = '../exp/testEGvsLU/input3/', set=3)
    main(inputFilesDir = '../exp/testEGvsLU/input4/', set=4)
    main(inputFilesDir = '../exp/testEGvsLU/input5/', set=5)

