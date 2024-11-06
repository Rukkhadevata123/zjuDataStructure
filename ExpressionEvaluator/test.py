import math

# Define the test expressions as strings to be evaluated
test_expressions = [
    "3.5 + 4.7e2 * +-.123 + (2 - -8) * 3",                
    "-3.5e-2 + 4 * -+-(2.5 + 5.5)",                       
    "+3.5e2 + +4.7e-2 * --5.5 + (+.123 - -8) * -3",       
    "+3.5 + -4.7e2 * -5 + (2 - -8) * +3 / -2 - +1",       
    "-3.5e2 + +4.7e-2 * -+-0.123 + (2 - 8) * 3 / 2 - +1 + 6e2", 
    "3.5e2 + 4.7e-2 * -.123 + +(2 - -8) * +3 / -2 - +1 + +6e-2", 
    "+3.5 + -4.7e2 * -5.5 + +(2 - 8) * -3 / 2 + +8e-2",   
    "--3.5 + +4 * -+-(2.5e-2 + .123)",                    
    "++3.5 + -4.7e2 * -.5 + +2e2 / 4 - .123e-2",          
    "+3.5 * (4.7e2 - +3e2 / +(2e-2 + .5))"                
]

# Evaluate each expression and print the result
for expr in test_expressions:
    try:
        result = eval(expr)
        print(f"Expression: {expr}")
        print(f"Result: {result}\n")
    except Exception as e:
        print(f"Expression: {expr} raised an error: {e}\n")
