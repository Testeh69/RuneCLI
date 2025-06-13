import matplotlib.pyplot as plt
import numpy as np
from sklearn.metrics.pairwise import cosine_similarity
from numpy.linalg import norm



x = (6,6)
y = (3,3)
z = (5,6)
d = (-6,-6)


list_points = [x, y, z, d]


### define new metrics to define what is the point that is the closest to the other one

def new_metrics(point1, point2):
    r = 0.5 #remanance
    new_metrics = r*np.exp(cosine_similarity([point1], [point2])[0][0]) * (norm(np.array(point1) - np.array(point2)))
    return new_metrics

def new_metrics2(point1, point2, alpha=0.5, beta=0.5):
    new_metrics = alpha * cosine_similarity([point1], [point2])[0][0] + beta * norm(np.array(point1) - np.array(point2))
    return new_metrics


for x in list_points:
    for y in list_points:
        if x != y:
            cos_sim = cosine_similarity([x], [y])[0][0]
            euclidean_dist = norm(np.array(x) - np.array(y))
            #print(f"Cosine Similarity between {x} and {y}: {cos_sim:.2f}")
            print(f"Euclidean Distance between {x} and {y}: {euclidean_dist:.2f}")
            print(f"New Metric between {x} and {y}: {new_metrics(x, y):.2f}")
            print(f"New Metric2 between {x} and {y}: {new_metrics2(x, y):.2f}")









