import subprocess as sp
import os
import json
from datetime import datetime

def main():
    now = datetime.now()
    currentTime = now.strftime("%Y%m%d_%H%M%S")

    pathToExe = "../../build/Release/BenchmarkEGvsLU.exe"
    repeat = 50

    inputFilesDir = '../exp/testEGvsLU/input/'
    results = []

    for filename in os.listdir(inputFilesDir):
        input_file = os.path.join(inputFilesDir, filename)
        if os.path.isfile(input_file) and input_file.endswith(".in"):
            datetime.now()
            print("[{0:}] processing {1:}".format(datetime.now().strftime("%Y-%m-%d %H:%M:%S"), filename))

            process = sp.Popen([pathToExe, input_file, str(repeat)], stdout=sp.PIPE)
            (output, err) = process.communicate()
            exitCode = process.wait()
            resultStr = output.decode('utf-8')
            results.append(json.loads(resultStr))

    outputFilename = '../exp/testEGvsLU/results_{:}.json'.format(currentTime)
    with open(outputFilename,'w', encoding='utf-8') as outputFile:
        outputFile.write(json.dumps(results, indent=4))

if __name__ == '__main__':
    main()
