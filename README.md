= API freezer

What is it ? It is a PoC/experiment to autogenerate plugins to "freeze" the VPP API

= How to use it ?

check it out into a directory outside the VPP tree, then go to the VPP tree, issue "make build"
and wait till it is successful, then issue the command like this:

```
~/api-frezer/freeze-api v1908
```

This will create a plugin called "apiv1908compat", that will create an API endpoint listener with the
given label.
