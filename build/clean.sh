#!/bin/bash

cat .gitignore | tr -d '/' | xargs rm -rf