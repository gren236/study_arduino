package main

import (
	"bufio"
	"fmt"
	"os"

	"github.com/tarm/serial"
)

func main() {
	c := &serial.Config{
		Name: "/dev/ttyACM0",
		Baud: 9600,
	}
	s, err := serial.OpenPort(c)
	if err != nil {
		panic("Failed to open serial port!")
	}
	defer s.Close()

	scanner := bufio.NewScanner(s)
	fmt.Println("-----TMP-----")
	fmt.Print("\033[s") // save the cursor position
	for scanner.Scan() {
		line := scanner.Bytes()

		if len(line) < 7 {
			continue
		}

		fmt.Print("\033[u\033[K") // restore the cursor position and clear the line

		fmt.Printf("| %s - %s |\n", line[0:3], line[4:7])
		fmt.Println("-------------")

		if err = scanner.Err(); err != nil {
			fmt.Fprintln(os.Stderr, "Failed to read:", err)
		}
	}
}
