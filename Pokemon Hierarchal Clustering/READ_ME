Goal: Perform hierarchical clustering on publicly available Pokemon stats. Each Pokemon is defined by a row in the data set. 
Because there are various ways to characterize how strong a Pokemon is, we summarize the stats into a shorter feature vector. 
For this project, I represented a Pokemon’s quality by 6 numbers:
HP, Attack, Defense, Sp. Atk, Sp. Def, Speed

Function Descriptions:

load_data(filepath) — takes in a string with a path to a CSV file, and returns the
data points as a list of dicts.

calc_features(row) — takes in one row dict from the data loaded from the previous
function then calculates the corresponding feature vector for that Pokemon as specified
above, and returns it as a numpy array of shape (6,). The dtype of this array should
be int64.

hac(features) — performs complete linkage hierarchical agglomerate clustering on
the Pokemon with the (x1, . . . , x6) feature representation, and returns a numpy array
representing the clustering

imshow_hac(Z) — visualizes the hierarchical agglomerate clustering on the Pokemon’s
feature representation.
