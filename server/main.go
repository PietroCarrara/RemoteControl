package main

import (
	"bufio"
	"fmt"
	"net"
	"strconv"
	"strings"

	uinput "github.com/sashko/go-uinput"
)

func main() {
	listener, _ := net.Listen("tcp", ":8080")

	for {
		conn, _ := listener.Accept()

		go serve(conn)
	}
}

func serve(conn net.Conn) {
	fmt.Println("Client connected")

	// Our uinput joystick
	js, err := uinput.CreateJoystick(0, 255, 0, 255, 15, 0)
	if err != nil {
		fmt.Printf("Couldn't create virtual joystick: %v\n", err)
		return
	}
	defer js.Close()

	buff := bufio.NewReader(conn)

	for {
		bytes := make([]byte, 128)
		n, _ := buff.Read(bytes)

		if n > 0 {
			msg := string(bytes)

			fmt.Println(msg)

			args := strings.Split(strings.Trim(msg, "\n\r\t\x00"), ":")

			resolve(args[0], args[1], args[2], js)
		}
	}
}

func resolve(operation string, arg1 string, arg2 string, js uinput.Joystick) {

	switch operation {
	case "SetState":
		setState(arg1, arg2, js)
	case "SetValue":
		setValue(arg1, arg2, js)
	}

}

func setState(btn, isDownStr string, js uinput.Joystick) {

	var isDown bool

	if isDownStr == "true" {
		isDown = true
	}

	var btnCode uint16
	switch btn {
	case "BTNA":
		btnCode = uinput.BtnSouth
	case "BTNX":
		btnCode = uinput.BtnWest
	case "BTNY":
		btnCode = uinput.BtnNorth
	case "BTNB":
		btnCode = uinput.BtnEast
	case "LTRIGGER":
		btnCode = uinput.BtnTL
	case "RTRIGGER":
		btnCode = uinput.BtnTR
	case "START":
		btnCode = uinput.BtnStart
	case "SELECT":
		btnCode = uinput.BtnSelect
	case "UP":
		btnCode = uinput.BtnDpadUp
	case "DOWN":
		btnCode = uinput.BtnDpadDown
	case "LEFT":
		btnCode = uinput.BtnDpadLeft
	case "RIGHT":
		btnCode = uinput.BtnDpadRight
	default:
		fmt.Printf("Unknown button: %s\n", btn)
		return
	}

	fmt.Printf("BT=%x\n", btnCode)

	if isDown {
		js.BtnDown(btnCode)
	} else {
		js.BtnUp(btnCode)
	}
}

func setValue(arg1, arg2 string, js uinput.Joystick) {

	_val, _ := strconv.Atoi(arg2)

	val := int32(_val)

	switch arg1 {
	case "LX":
		js.LeftStickX(val)
	case "LY":
		js.LeftStickY(val)
	case "RX":
		js.RightStickX(val)
	case "RY":
		js.RightStickY(val)
	}

}
