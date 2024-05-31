import time
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from subprocess import run

calls = ["python parse_and_write.py html5lib",
         "python parse_and_write.py lxml",
         "python parse_and_write.py html.parser",
         "../cmake-build-release/parse_and_write"]

# calls = ["python find_all_links.py html5lib",
#          "python find_all_links.py lxml",
#          "python find_all_links.py html.parser",
#          "../cmake-build-release/find_all_links"]


if __name__ == "__main__":
    run_count = 30
    times = np.zeros((run_count, len(calls)))
    for i, cmd in enumerate(calls):
        print("\n" + cmd)
        for j in range(run_count):
            parsed_time = int(run(cmd, shell=True, capture_output=True).stdout.decode("utf-8"))
            print(parsed_time)
            times[j, i] = parsed_time

df = pd.DataFrame(times, index=range(run_count), columns=["bs4+html5lib", "bs4+lxml", "bs4+html.parser", "soupcxx"])
print(df)
print(df.describe())
medians = df.median()
std_devs = df.std()

fig, ax = plt.subplots()
medians.plot(kind='bar', yerr=std_devs, ax=ax, capsize=4)
ax.set_ylabel('Time (µs)')
ax.set_title('Time to Parse and Prettify alice_large.html')
# ax.set_title('Time to Parse and Find All Links in alice_large.html')

plt.xticks(rotation=45, ha='right')
plt.tight_layout()
plt.savefig('parse_and_write.png')
plt.savefig('parse_and_write.pdf')
# plt.savefig('find_all_links.png')
# plt.savefig('find_all_links.pdf')
