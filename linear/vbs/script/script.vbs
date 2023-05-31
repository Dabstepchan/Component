Set app = CreateObject("IKS.Application")

matrix = Array(Array(1.0, 2.0, 3.0), Array(4.0, 5.0, 6.0), Array(7.0, 8.0, 9.0))
vector = Array(1.0, 2.0, 3.0)

result = app.CalculateDeterminant(matrix)
WScript.Echo "Determinant: " & result

solution = Array()
app.SolveSystemDecomposition(matrix, vector, solution)
WScript.Echo "Solution: "
For i = 0 To UBound(solution)
    WScript.Echo solution(i)
Next

