#  :globe_with_meridians Elections-project

In an anonymous country we complained about the forgery of the election results, so it was decided to build the election management system:

- The state is divided into districts, where each district is associated with a number of representatives according to it's size (for example:NY County has 29 delegates).

- Each party running in the elections has a single candidate for head of state, and a separate list of representatives for each County in the country. 

- Every citizen votes in the district where he lives for one of the parties running in the election.

- The identity of the representatives in each district is determined by the list of each party in the district, according to the ratio of votes received.

- At the end of the election, each district is associated with the party that received the most votes in the district. head of state
The chosen one is the one who won the districts with the largest sum of representatives.

 ### :notebook: For each round of elections, the following data must be saved:

• Date on which the election round takes place (day, month, year).

• Voter Book: List of eligible citizens. Every citizen must keep his name, a number His identity card, his year of birth and the district to which he is associated.

• List of nominated parties: Each party must keep its name, the party's candidate for leadership The state, and the list of representatives on behalf of the party to each district, are sorted by order. Every representative is a citizen.

• District: List of districts in the country. Each district has a name, a serial number, a list of eligible citizens
Voting in the District, Percentage of Citizens, and Election Results: Which Representatives Are Elected
From any party.
