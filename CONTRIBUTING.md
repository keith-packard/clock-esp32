# Contributing to clock-esp32

We welcome contributions of all forms, including patches to code and
documentation, issue reports, or just kind words.

## Getting Current Source Code

Clock-esp32 sources are maintained in git and hosted in two places.

 1. [keithp.com](https://keithp.com/cgit/clock-esp32.git/). This is the
    'canonical' source location.

 2. [github](https://github.com/keith-packard/clock-esp32). This should
    exactly mirror the code at keithp.com. I've placed it here to
    make contributing to this project easier for people familiar with github.

You can create a local copy of the repository with git clone:

	$ git clone git://keithp.com/git/clock-esp32.git

or

	$ git clone https://github.com/keith-packard/clock-esp32.git

## Building from Source

Clock-esp32 wraps the esp32 SDK with simple Makefiles.

	$ cd clock-esp32
	$ make

## Patch Submission

You can submit patches in a couple of ways:

 1. Mail to the snek list (see below). This can be tricky as it
    requires a friendly email system, and you'll have to subscribe to
    the mailing list before it will let you post anything
    (sigh). Here's a simple example sending the latest patch in your
    local repository to the list:

	$ git send-email --to snek@keithp.com HEAD^

 2. Generate a pull-request in github.

    1. Fork the project into your own github account
    2. Push patches to that repository
    3. While viewing your repository, click on the 'New pull request'
       button and follow the instructions there.

## Issue Tracking

We're using the issue tracker on Github for now; if you have issues,
please submit them to the
[Clock-esp32 Issue Tracker](https://github.com/keith-packard/clock-esp32/issues)

## Mailing List

You can use the snek mailing list to talk about this project. That
list is hosted at keithp.com. You can [subscribe
here](https://keithp.com/mailman/listinfo/snek).  This is a public
list, with public archives. Participants are expected to abide by the
Snek Code of Conduct.

## Code of Conduct

Clock-esp32 uses the
[Contributor Covenant](https://www.contributor-covenant.org/), which
you'll find in the source tree. Please help make this project a kind and
welcoming environment by following those rules.
