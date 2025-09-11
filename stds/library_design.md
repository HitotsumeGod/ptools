# PTOOLS Standards for C Program Design
# # With a 'Program' Encapsulated in the Concept of the 'Project'

Functions should always be prefixed according to their Scope of Operation.
A Scope of Operation is the abstract 'area' within which a function operates
and shares comrades. One Scope is always defined for any given project: the
Core Project Scope, which essentially contains the project's unique
functionality; essentially, any logic that could never be reused in any
other project: such logic makes sense only within the scope of its parent
project, as opposed to logic that could be shared in other projects someday.
For example, in the WIFEY project, there are two primary scopes that can be
seen frequently when browsing the API:<br>

The "wifey" scope, being the project's CPS, which constitutes all functions
that provide logic and or features extremely specific to WIFEY, such as
parsing or printing the contents of a radiotap header. While similar logic
might be implemented in another project some day, it will necessarily be
unique from WIFEY's logic, which is why the scope is considered core to the
project.<br>

The "nl" scope, being a Scope related to all NL
