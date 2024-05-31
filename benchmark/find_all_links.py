import bs4
import time
import sys

parser = sys.argv[1]
total_time = 0

for i in range(30):
    with open('../data/alice_large.html') as f:
        start = time.time()
        soup = bs4.BeautifulSoup(f, parser)
        links = soup.find_all("a")
        end = time.time()
        total_time += int((end - start) * 1_000_000)
print(total_time)

with open("../data/alice_links_bs4.html", "w") as f:
    f.write("\n".join([link["href"] for link in links]))