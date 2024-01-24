using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    //// Start is called before the first frame update
    //void Start()
    //{

    //}
    public float speed;
    public bool isTouch_Top;
    public bool isTouch_Bottom;
    public bool isTouch_Right;
    public bool isTouch_Left;

    Animator animator;

    private void Awake()
    {
        animator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        float h = Input.GetAxisRaw("Horizontal");
        if ((isTouch_Right && h == 1) || (isTouch_Left && h == -1))
            h = 0;
        float v = Input.GetAxisRaw("Vertical");
        if ((isTouch_Top && v == 1) || (isTouch_Bottom && v == -1))
            v = 0;
        Vector3 curPos = transform.position;
        //Transform ¿Ãµø¿∫ ∞ˆ«ÿ¡‡æﬂ«—¥Ÿ. 1∫Œ∞≠¡¬ »Æ¿Œ
        Vector3 nextPos = new Vector3(h, v, 0) * speed * Time.deltaTime;

        transform.position = curPos + nextPos;

        if (Input.GetButtonDown("Horizontal") ||
            Input.GetButtonUp("Horizontal"))
        {
            animator.SetInteger("Input", (int)h);
        }
    }

    void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Border")
        {
            switch (collision.gameObject.name)
            {
                case "Top":
                    isTouch_Top = true;
                    break;
                case "Bottom":
                    isTouch_Bottom = true;
                    break;
                case "Right":
                    isTouch_Right = true;
                    break;
                case "Left":
                    isTouch_Left = true;
                    break;
            }
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Border")
        {
            switch (collision.gameObject.name)
            {
                case "Top":
                    isTouch_Top = false;
                    break;
                case "Bottom":
                    isTouch_Bottom = false;
                    break;
                case "Right":
                    isTouch_Right = false;
                    break;
                case "Left":
                    isTouch_Left = false;
                    break;
            }
        }
    }

}
