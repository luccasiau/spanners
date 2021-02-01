import numpy as np

class EuclideanSpanner:
  """
  Class to represent Euclidean Spanners. Supports D-dimensions, but it's designed
  with only 2 in mind.

  Constructor takes:
    - a pointset dictionary, containing label (so important that it's required)
    and coordinates as an array. Updates to pointset are not supported.
    - edge list. Should contain a list of 2-dimensional arrays, each of those
    containing the labels of two vertices. Arrays with invalid labels will be
    silently ignored.
  """

  # PUBLIC METHODS -------------------------------------------------------------
  def __init__(self, pointset, edges):
    self.__pointset = {p: np.array(pointset[p]) for p in pointset.keys()}
    self.__stretch = np.inf
    
    self.__degree = {p: 0 for p in pointset.keys()}

    self.__sp_matrix = {
      p1: {p2: (np.inf if p1 != p2 else 0) for p2 in self.__pointset.keys()}
      for p1 in self.__pointset.keys()
    }

    self.__adj_matrix = {
      p1: {p2: (False if p1 != p2 else True) for p2 in self.__pointset.keys()}
      for p1 in self.__pointset.keys()
    }

    for edge in edges:
      self.add_edge(edge[0], edge[1], update_sp = False)
    self.update_sp()
    pass

  # Setting update_sp to False allows you to skip recalculationg of APSP.
  # This flag should only be set to False if several of these operations are
  # being made consecutively, and the last one of them sets it to True.
  # Otherwise, it is INCREDIBLY DANGEROUS.
  # Silently ignores if edge already exists.
  def add_edge(self, p1, p2, update_sp = True):
    if self.__adj_matrix[p1][p2] == True:
      return

    self.__adj_matrix[p1][p2] = True
    self.__adj_matrix[p2][p1] = True
    self.__degree[p1] += 1
    self.__degree[p2] += 1

    if update_sp:
      update_sp()

  # See above nodes on update_sp.
  # Silently ignores if edge doesn't exist.
  def remove_edge(self, p1, p2, update_sp = True):
    if self.__adj_matrix[p1][p2] == False:
      return

    self.__adj_matrix[p1][p2] = False
    self.__adj_matrix[p2][p1] = False
    self.__degree[p1] -= 1
    self.__degree[p2] -= 1

    if update_sp:
      update_sp()

  # Run Floyd-Warshall's algorithm on the graph's adjacency matrix.
  def update_sp(self):
    for i in self.__pointset.keys():
      for j in self.__pointset.keys():
        self.__sp_matrix[i][j] = self.__dist(i, j) if self.__adj_matrix[i][j]\
          else np.inf

    for k in self.__pointset.keys():
      for i in self.__pointset.keys():
        for j in self.__pointset.keys():
          self.__sp_matrix[i][j] = min(self.__sp_matrix[i][j],\
            self.__sp_matrix[i][k] + self.__sp_matrix[k][j])

    self.__update_stretch()

  # Returns stretch between two points in the graph.
  # Returns 1 if p1==p2
  def pair_stretch(self, p1, p2):
    return 1 if p1 == p2 else self.__sp_matrix[p1][p2] / self.__dist(p1, p2)

  # Returns stretch of entire graph
  def stretch(self):
    return self.__stretch

  # Returns max degree in the graph
  def max_degree(self):
    return np.max(self.__degree.values())

  # Returns point labels
  def labels(self):
    return self.__pointset.labels()

  # "PRIVATE" METHODS ----------------------------------------------------------
  # Euclidean Distance between points label_a, label_b
  def __dist(self, label_a, label_b):
    return np.linalg.norm(self.__pointset(label_a) - self.__pointset(label_b))

  def __update_stretch(self):
    self.__stretch = np.max([
      [self.pair_stretch(i, j) for j in self.__pointset.keys()]
      for i in self.__poinset.keys()]
    )