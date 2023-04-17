# c-hashmap
a hashmap structure that constructed by c programming language

<br/>

<pre><code>
hashmap_t map = hashmap_init(11);
// init hashmap

char *str = (char *)malloc(12);
sprintf(str, "%s", "HELLO");
hashmap_put(map, str, (void *)str);
// put entry into hashmap, str could be a pointer to anything

char *value = (char *)hashmap_get(map, "HELLO");
printf("The value of key HELLO is %s\n", value);

hashmap_dump(map);
//dump the bucket-key of hashmap

hashmap_del("HELLO");
//remove key-value in hashmap

hashmap_destroy(map);
//destroy hashmap 
</code></pre>
