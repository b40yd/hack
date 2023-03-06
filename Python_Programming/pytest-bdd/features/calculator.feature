Feature: Calculator

Scenario: Add two numbers
    Given I have a calculator
    When I add 3 and 20
    Then the result should be 23
