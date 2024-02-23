import 'dart:io';
import 'dart:convert';

main() async {
  List<String> args = Arguments.args;

  if (args.length < 3 || args.length % 2 != 0) {
    stdout.writeln('Usage: ${arguments.scriptName} number1 operator number2 ...');
    exit(1);
  }

  List<double> operands = [];
  String currentArg;
  double currentOperand;

  for (int index = 0; index < args.length; index += 2) {
    currentArg = args[index];

    if (currentArg.isNumeric) {
      currentOperand = parseDouble(currentArg);
      operands.add(currentOperand);
    } else {
      switch (currentArg) {
        case '+':
          break;
        default:
          stderr.writeln('Invalid operator: $currentArg');
          exit(1);
      }
    }
  }

  double sum = 0.0;
  for (int i = 0; i < operands.length - 1; i++) {
    sum += operands[i];
  }

  sum += parseDouble(args.last);

  String result = 'Sum: ${sum.toStringAsFixed(2)}';
  File('cpu_instance.txt').writeAsStringSync(result);
  stdout.writeln(result);
}

bool isNumeric(String strNum) {
  try {
    double.parse(strNum);
    return true;
  } catch (e) {
    return false;
  }
}

double parseDouble(String strNumber) {
  return double.parse(strNumber);
}
