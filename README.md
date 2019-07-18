# hash_table.h

_hash_table.h_ is a header-only generic hash_table implementation in C. It utilizes (abuses?) the C preprocessor to be provide a level of generality near C++ templates like the STL’s std::unordered\_map.

## Using ##
To use _hash_table.h_, you must first `#include "hash_table.h"` in your source code. For every type that you wish to hold in a hash_table, EXACTLY ONE 'using' statement is required:

```C
/* main.c */
#include "hash_table.h"

use_hash_table(float, int);

...
```
If the either the key type or the value type is referenced with anything but a bare identifier (e.g. `char *`, `float[10]`), it must first be wrapped in a typedef:

```C
/* main.c */
#include "hash_table.h"

typedef char * str;

use_hash_table(str, double);

...
```

After that, you may use any of the following macro-like functions to create, destroy, and operate on hash_tables and their iterators.

`hash_table_make(key_type, value_type, hash)`        - Allocates, initializes, and returns a new hash_table with the hash function `hash`.

`hash_table_make_e(key_type, value_type, hash, equ)` - Allocates, initializes, and returns a new hash_table with the hash function `hash`, and the key equality function `equ`.

`hash_table_free(t)`                                 - `free()`s the hash_table. This does NOT deallocate hash_table keys or values.

`hash_table_len(t)`                                  - Returns the number of hash_table elements.

`hash_table_get_key(t, key)`                         - Search the hash_table for `key`. Returns a a pointer to the corresponding key, or NULL if not found.

`hash_table_get_val(t, key)`                         - Search the hash_table for `key`. Returns a a pointer to the corresponding value, or NULL if not found.

`hash_table_insert(t, key, val)`                     - Add the `key`, `val` pair to the hash_table or update the value associated with the key if it already exists.

`hash_table_delete(t, key)`                          - Remove `key` and its value from the hash_table. Returns `1` if the key was found, `0` otherwise.

`hash_table_traverse(t, key, val_ptr)`               - Shorthand for a `for` loop that visits every hash table key/value pair in an unspecified order. Assigns the element key to `key` by value and assigns a pointer to the corresponding value to `val_ptr`.

See _hash_table_test.c_ for examples of using _hash_table.h_'s interface.


### Note ###
_hash_table.h_ requires the C preprocessor's \_\_VA\_ARGS\_\_ and so requires that it is compiled in C99 mode.

## Download ##
You can clone the project with [Git](http://git-scm.com "Git") by running:

    $ git clone git://github.com/kammerdienerb/hash_table.h

