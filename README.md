# c-hashmap
a hashmap structure that constructed by c programming language

<br/>

<pre><code>
hashmap_t map = hashmap_init();
// init hashmap


char *str = (char *)malloc(12);
sprintf(str, "%s", "HELLO");
hashmap_put(map, str, (void *)str);
// put entry into hashmap, str could be a pointer to anything


hashmap_dump(map);
//dump the bucket-key of hashmap

hashmap_remove("HELLO");
//remove key-value in hashmap

hashmap_destroy(map);
//destroy hashmap 
</code></pre>
