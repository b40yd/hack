import logging
from re import T
from pytest_bdd import scenarios, given, when, then,parsers
from pytest import fixture
import logging

class Calculator:

    def __init__(self):
        self.result = 0
    def add(self,a, b):
        self.result = a+b
    def subtract(self,a, b):
        self.result= a-b

logging.basicConfig(filename='test.log', level=logging.DEBUG)

scenarios("../features/calculator.feature")

@fixture
@given("I have a calculator")
def calculator():
    return Calculator()

@when(parsers.parse('I add {x} and {y}'))
def add(calculator, x, y):
    calculator.add(int(x), int(y))

@then(parsers.cfparse('the result should be {result}'))
def check_result(calculator, result):
    logging.debug("====== {}, {} ====".format(calculator.result,result))
    assert calculator.result == int(result)

# @when(parsers.cfparse('I add {x:T} and {y:T}', extra_types=dict(T=int)))
# def add(calculator, x, y):
#     calculator.add(x, y)

# @then(parsers.cfparse('the result should be {result:T}', extra_types=dict(T=int)))
# def check_result(calculator, result):
#     logging.debug("====== {}, {} ====".format(calculator.result,result))
#     assert calculator.result == result


