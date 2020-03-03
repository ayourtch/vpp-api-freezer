
# API freezer

What is it ? It is a PoC/experiment to autogenerate plugins to "freeze" the VPP API.

Again: this is an *EXPERIMENT* - intended to explore the possibilities. Don't use it for anything
at the moment.

# How to use it ?

check it out into a directory *outside* the VPP tree, then go to the VPP tree, check out the stable/1908 branch,
issue "make build" and wait till it is successful, then issue the command like this:

```
~/api-frezer/freeze-api v1908
```

This will create a plugin called "apiv1908compat", that will create an API endpoint listener with the
given label "v1908". It will also create a series of CLI commands "show api v1908 ..." which will function
similar to the familiar "show api ..." ones. 

# Caveats / quirks / findings

## Message structure inconsistency / lack of ability to introspect

All requests have the client\_index field, and *most* of the messages have context\_id, but the latter
is not the case for all messages - a dozen or so of them do not. Also, the "request" and "reply" are impossible
to know of at compile time, leading to unnecessary overhead.

## Symbol/paths renaming using sed/perl

This is a fairly coarse brush - something a bit gentler would make it more robust. Or maybe just cleverer regexes.

## API message enum definition

Sometime between 1908 and 2001 there appears to have been a change with how to include the message enum definitions
and message-crc-ID triplets. 

## copyout of API endpoint sources

While it kind of works, probably a more scalable approach would be to have the necessary functionality available
on a more a library basis. However, this of course would limit the changes possible - but probably should not be a big deal.


