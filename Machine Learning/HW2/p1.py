def perceptron_update(weights, bias, x, y):
    prediction = sum(w * x_i for w, x_i in zip(weights, x)) + bias
    
    if y * prediction <= 0:
        weights = [w + y * x_i for w, x_i in zip(weights, x)]
        bias += y

    return weights, bias

weights = [0, -1]
bias = 0.5
samples = [
    ([0, 0], -1),
    ([0, 1], 1),
    ([1, 0], 1),
    ([1, 1], 1)
]

converged = False
epoch = 0
while not converged:
    converged = True
    epoch += 1
    for x, y in samples:
        old_weights, old_bias = weights[:], bias
        weights, bias = perceptron_update(weights, bias, x, y)
        if weights != old_weights or bias != old_bias:
            converged = False
    print(f"Epoch {epoch}: weights = {weights}, bias = {bias}")

print(f"Final weights = {weights}, final bias = {bias}")
