################################################################################
############################### --- Imports --- ################################
################################################################################

# general packages
import argparse
from email import header
import math
import statistics

# data science related packages
import pandas as pd


################################################################################
################################ --- Params --- ################################
################################################################################
# -----------------------------------
# Data - Inputs & Outputs
# -----------------------------------
# column names for raw input data
input_column_headers = [
	"Tree Structure","Tree Storage","Traversal Type","Traversal Callback",
	"Tree Size","Tree Depth","Leaf Nodes","Leaf Density","# of Samples",
	"Total Cycles","Total Seconds","Avg. Cycles","Avg. Seconds",
]

# columns used for ids when reshaping data (and calculating means/stddevs)
id_columns = [
	"Tree Structure","Tree Storage","Traversal Type","Traversal Callback",
]

# names of the metrics output after parsing + reshaping
metric_columns = [
	"mean_cycles", "mean_seconds", "mean_log(cycles)", "mean_log(seconds)",
	"std_cycles", "std_seconds", "std_log(cycles)", "std_log(seconds)",
]

# -----------------------------------
# Miscellaneous
# -----------------------------------



################################################################################
############################# --- Data Parsing --- #############################
################################################################################

def getRowID(row):
	return tuple( row[c] for c in id_columns );

def getOutputFile(input_file):
	file_split = input_file.split("/")
	file_split[-1] = "cleaned-" + file_split[-1]
	return "/".join(file_split)

def loadData(input_file):
	raw_data = pd.read_csv(input_file)
	return raw_data

def reshapeData(raw_data):
	# get unique N values in data (will be stored as lgN, specifically lg(N+1))
	N_values = (raw_data["Tree Size"]).unique()
	N_values.sort()
	# print(N_values)
	lgN_values = [ int(math.log2(n+1)) for n in N_values]
	# print(lgN_values)
	N_mapping = {}
	for i in range(len(N_values)):
		N_mapping[N_values[i]] = i

	# save data into a new data dictionary (which we will use to calc means and std devs)
	data_dict = {}
	for index, row in raw_data.iterrows():
		row_id = getRowID(row)

		if row_id not in data_dict:
			data_dict[row_id] = [{
				"seconds": [],
				"cycles": [],
				"mean_cycles": 0,
				"mean_seconds": 0,
				"std_cycles": 0,
				"std_seconds": 0,
				"log(seconds)": [],
				"log(cycles)": [],
				"mean_log(cycles)": 0,
				"mean_log(seconds)": 0,
				"std_log(cycles)": 0,
				"std_log(seconds)": 0,
				"samples": 0,
			} for n in N_values]

		N_index = N_mapping[row["Tree Size"]]
		sample_dict = data_dict[row_id][N_index]
		sample_dict["samples"] += 1
		sample_dict["cycles"].append(row["Avg. Cycles"])
		sample_dict["seconds"].append(row["Avg. Seconds"])
		sample_dict["log(cycles)"].append(math.log(row["Avg. Cycles"]) if row["Avg. Cycles"] > 0 else -math.inf)
		sample_dict["log(seconds)"].append(math.log(row["Avg. Seconds"]) if row["Avg. Seconds"] > 0 else -math.inf)
	
	# calculate means and standard deviatons for each category
	for category, category_samples in data_dict.items():
		for sample in category_samples:
			if (sample["samples"] > 0):
				sample["mean_cycles"] = statistics.mean(sample["cycles"])
				sample["mean_seconds"] = statistics.mean(sample["seconds"])
				sample["mean_log(cycles)"] = statistics.mean(sample["log(cycles)"])
				sample["mean_log(seconds)"] = statistics.mean(sample["log(seconds)"])
			if (sample["samples"] > 1):
				sample["std_cycles"] = statistics.stdev(sample["cycles"])
				sample["std_seconds"] = statistics.stdev(sample["seconds"])
				sample["std_log(cycles)"] = statistics.stdev(sample["log(cycles)"])
				sample["std_log(seconds)"] = statistics.stdev(sample["log(seconds)"])

	# reshape this data into a new dataframe
	parsed_data = pd.DataFrame({
		"Tree Size": N_values,
		"lg(Tree Size)": lgN_values,
	});
	current_column_index = 2
	for metric in metric_columns:
		for category, category_samples in data_dict.items():
			column_name = " ".join(category) + " " + metric
			column_data = [s[metric] for s in category_samples]
			parsed_data.insert(current_column_index, column_name, column_data)
			current_column_index += 1

	return parsed_data

def saveData(parsed_data, output_file):
	parsed_data.to_csv(output_file, index=False)



################################################################################
#########################$#### --- Graph Gen. --- ##############################
################################################################################

def genGraph():
	pass

def genAllGraphs():
	pass



################################################################################
############################# --- Arg. Parser --- ##############################
################################################################################

def parse_arguments():
	"""
	Parser command line arguments and displays help text.

	Returns:
			args: parsed arguments passed into script through command line
	"""

	parser = argparse.ArgumentParser(description="Creates graphs for displaying"
		" results of traversal experiments. Was developed for the data"
		" collected from the native C code/experiments."
	)
	parser.add_argument(
		'-i',
		'--input_file', 
		type=str, 
		help='<Required> Input file with experimental data.', 
		required=True,
	)
	parser.add_argument(
		'-o',
		'--output_file', 
		type=str, 
		help='<Optional> Output file to save reformatted data.', 
	)
	args = parser.parse_args()
	return args


################################################################################
################################# --- Main --- #################################
################################################################################

def main():
	# grab args
	args = parse_arguments()
	input_file = args.input_file
	output_file = args.output_file if args.output_file else getOutputFile(input_file)

	# get input data
	raw_data = loadData(input_file)
	# print(raw_data.info(), "\n")
	# print(raw_data, "\n")

	# parse and reshape data
	parsed_data = reshapeData(raw_data)
	# print(parsed_data.info(), "\n")
	print(parsed_data, "\n")

	# save data to csv file
	saveData(parsed_data, output_file)



if __name__ == "__main__":
	main()


# ################################################################################
# ############################# --- End of File --- ##############################
# ################################################################################