using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using System.IO.Ports;

public class conexion_u_a : MonoBehaviour
{
    //ROTACION DE BARRILES
    public List<GameObject> barriles;

    //GAMEOVER
    public GameObject perdisteUI;




    //CONEXION
    bool isConnected = false;
    SerialPort port;
    string[] ports;
    public Dropdown lista;
    string portname;


    void DropdownItemSelected(Dropdown lista)
    {
        int indice = lista.value;
        portname = lista.options[indice].text;
    }

    public int String_TO_Int(string cadena)
    {
        int resul_final = 0;
        int longitu_palabra = cadena.Length;
        int[] arreglo_de_ints = new int[longitu_palabra];
        for (int i = 0; i < cadena.Length; i++)
        {
            arreglo_de_ints[i] = (int)char.GetNumericValue(cadena[i]);
            longitu_palabra -= 1;
            resul_final = ((int)Mathf.Pow(10, longitu_palabra)) * arreglo_de_ints[i] + resul_final;
        }
        return resul_final;
    }

    #region CONECTAR
    public void conectar()
    {
        if (!isConnected)
        {
            connect_to_Arduino();
        }
    }

    void connect_to_Arduino()
    {
        isConnected = true;
        port = new SerialPort(portname, 9600, Parity.None, 8, StopBits.One);

        port.Open();
        port.Write("#STAR\n");
    }
    #endregion

    #region DESCONECTAR
    public void desconectar()
    {
        if (isConnected)
        {
            disconnect_from_Arduino();
        }

    }

    void disconnect_from_Arduino()
    {
        isConnected = false;
        port.Write("#STOP\n");
        port.Close();


    }
    #endregion

    private void Awake()
    {
        lista.options.Clear();
        ports = SerialPort.GetPortNames();

        foreach (string port in ports)
        {
            lista.options.Add(new Dropdown.OptionData() { text = port });
        }

        DropdownItemSelected(lista);
        lista.onValueChanged.AddListener(delegate { DropdownItemSelected(lista); });
    }



    void Update()
    {
        if (isConnected) 
        {
            
            string estado = port.ReadLine();
            string perdiste = port.ReadLine();
            perdiste.Replace(" ", String.Empty);
            Debug.Log(estado);
            Debug.Log(perdiste);
            int estado_trans = String_TO_Int(estado);
            funcionRotacionBarriles(50, estado_trans);
            if (perdiste != "NOLOSE") 
            {
                perdisteUI.gameObject.SetActive(true);
            }
            
            
        }

    }

    void funcionRotacionBarriles(int rotacion, int balde) 
    {
        balde -= 1;
        if (balde == 0)
        {
            barriles[balde].transform.rotation = Quaternion.AngleAxis(-rotacion, Vector3.right);
        }

        else if(balde == 1)
        {
            barriles[balde].transform.rotation = Quaternion.AngleAxis(-rotacion, Vector3.right);
        }

        else if (balde == 2)
        {
            barriles[balde].transform.rotation = Quaternion.AngleAxis(-rotacion, Vector3.right);
        }

        else
        {
            barriles[0].transform.rotation = Quaternion.AngleAxis(0, Vector3.right);
            barriles[1].transform.rotation = Quaternion.AngleAxis(0, Vector3.right);
            barriles[2].transform.rotation = Quaternion.AngleAxis(0, Vector3.right);
        }
    }
}
