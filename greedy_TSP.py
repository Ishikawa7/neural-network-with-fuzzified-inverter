# Implement a greedy algorithm to solve TSP given a distance matrix

def greedy_tsp(dist_matrix):
    """
    :param dist_matrix: distance matrix
    :return: a list of points in order
    """
    # initialize the list of points
    points = [0]
    # initialize the list of unvisited points
    unvisited_points = list(range(1, len(dist_matrix)))
    # initialize the total distance
    total_dist = 0
    # loop until all points are visited
    while len(unvisited_points) > 0:
        # find the nearest city
        nearest_point = unvisited_points[0]
        nearest_dist = dist_matrix[points[-1], nearest_point]
        for city in unvisited_points:
            if dist_matrix[points[-1], city] < nearest_dist:
                nearest_point = city
                nearest_dist = dist_matrix[points[-1], city]
        # add the nearest city to the list
        points.append(nearest_point)
        # remove the nearest city from the list of unvisited points
        unvisited_points.remove(nearest_point)
        # update the total distance
        total_dist += nearest_dist
    # add the distance from the last city to the first city
    total_dist += dist_matrix[points[-1], points[0]]
    return points, total_dist