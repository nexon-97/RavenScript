# RavenScript Grammar expressions #

Abbreviations:

- **prog** - Program
- **expr** - Expression
- **stmt** - Statement
- **id** - Identifier
- **numb** - Number
- **e** - Empty

>*id* ->
>
>- **A-Z** *id* |
>- **a-z** *id* |
>- _ *id* |
>- **$** *id* |
>- **e**

>*numb* ->
>
>- **0-9** *numb* |
>- **e**

>*prog* ->
>
>- *stmt* *prog* |
>- **e**

>*stmt* ->
>
>- **require** *module* |
>- *lvalue* **=** *expr* |
>- *lvalue* **=** *numb* |
>- *expr*

>*module* ->
>
>- *id* |
>- *module* **.** *id*

>*lvalue* ->
>
>- *id*

>*expr* ->
>
>- **(** *expr* **)** |
>- *id* **.** *expr* |
>- *id* **(** *expr* **)**