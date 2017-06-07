# [normalrandom]

`[normalrandom]` generates normally-distributed random numbers in Max, using the Box-Muller transform.

## Using

Clone this repository into `Documents/Max 7/Packages` (or whatever the exact
path is on your Mac or Windows computer).

You should then be able to use the `[normalrandom]` object and access its `.maxhelp`
patcher.

## Developing

For Mac and PC:

- Download the [Max SDK](https://github.com/Cycling74/max-sdk)
- Clone this repository into `source`
- Open Visual Studio or Xcode project file in `normalrandom/source` and build
  (2x on Windows)
- Find build in SDK `externals` directory and copy to `externals` directory here

On Windows, the Visual Studio project was saved with VS Community 2017 on Windows 10.

On Mac, the Xcode project was saved with v8.3.3.
