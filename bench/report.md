---
geometry:
  - margin=0.75in
  - letterpaper
papersize: a4
author: "Mark Marolf mmarolf@ethz.ch"
date: "10/10/2025"
header-includes: |
  \usepackage{fancyhdr}
  \usepackage{lastpage}
  \pagestyle{fancy}
  \fancyhead[L]{mmarolf@ethz.ch}
  \fancyhead[C]{}
  \fancyhead[R]{\thepage/\pageref{LastPage}}
  \fancyfoot[C]{}
---

<!-- pandoc report.md --to=pdf -o report.pdf --pdf-engine=xelatex -->

# Lab 1: Simulating and Exploring Cache Behavior

## Introduction

## Cache Implementation Design

## Experimental Methodology

### Benchmark Suite

### Measurement and Metrics

### Parameter Sweep

## Results and Discussion

### Effect of Cache Size

### Effect of Block Size

### Effect of Associativity

### Replacement Policy Comparison

### Discussion of Observations

## Appendix

![Cache Size Effect](./plots/cache_size.eps)