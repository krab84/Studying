//#define BEFORE_LOGIC
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

#if BEFORE_LOGIC
public class Enemy : MonoBehaviour
{
    public float speed;
    public int health;
    public Sprite[] sprites;

    SpriteRenderer spriteRenderer;
    Rigidbody2D rigid;

    private void Awake()
    {
        spriteRenderer = GetComponent<SpriteRenderer>();
        rigid = GetComponent<Rigidbody2D>();
        rigid.velocity = Vector2.down * speed;
    }

    void OnHit(int dmg)
    {
        health -= dmg;
        spriteRenderer.sprite = sprites[1];
        Invoke("ReturnSprite", 0.1f);
        if (health <= 0) {
            //Destroy(this);
            Destroy(gameObject);
        }
    }

    void ReturnSprite()
    {
        spriteRenderer.sprite = sprites[0];
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.gameObject.tag == "BorderBullet")
        {
            Destroy(gameObject);
        }
        else if (collision.gameObject.tag == "PlayerBullet")
        {
            Bullet bullet = collision.gameObject.GetComponent<Bullet>();
            OnHit(bullet.dmg);
            Destroy(collision.gameObject);
        }
    }
}
#else
public class Enemy : MonoBehaviour
{
    public string enemyName;
    public int enemyScore;
    public float speed;
    public int health;
    public Sprite[] sprites;

    //장전속도
    public float maxShotDelay;
    public float curShotDelay;

    public GameObject bulletObjectA;
    public GameObject bulletObjectB;
    public GameObject player;

    SpriteRenderer spriteRenderer;

    private void Awake()
    {
        spriteRenderer = GetComponent<SpriteRenderer>();
    }

    void OnHit(int dmg)
    {
        health -= dmg;
        spriteRenderer.sprite = sprites[1];
        Invoke("ReturnSprite", 0.1f);
        if (health <= 0)
        {
            Player playerLogic = player.GetComponent<Player>();
            playerLogic.score += enemyScore;
            //Destroy(this);
            Destroy(gameObject);
        }
    }

    void ReturnSprite()
    {
        spriteRenderer.sprite = sprites[0];
    }

    // Update is called once per frame
    void Update()
    {
        FireBullet();
    }

    void FireBullet()
    {
        if (Time.time > curShotDelay)
        {
            curShotDelay = Time.time + maxShotDelay;
            if (enemyName == "S")
            {
                GameObject bullet = Instantiate(bulletObjectA, transform.position, transform.rotation);
                Rigidbody2D rigid = bullet.GetComponent<Rigidbody2D>();
                Vector3 dirVec = player.transform.position - transform.position;
                rigid.AddForce(dirVec.normalized * 3, ForceMode2D.Impulse);
            }
            //else if (enemyName == "M")
            //{
            //    GameObject bullet = Instantiate(bulletObjectA, transform.position, transform.rotation);
            //    Rigidbody2D rigid = bullet.GetComponent<Rigidbody2D>();
            //    Vector3 dirVec = player.transform.position - transform.position;
            //    rigid.AddForce(dirVec * 10, ForceMode2D.Impulse);
            //}
            else if (enemyName == "L")
            {

                {
                    GameObject bulletR = Instantiate(bulletObjectB, (transform.position + Vector3.right * 0.3f), transform.rotation);
                    Rigidbody2D rigidR = bulletR.GetComponent<Rigidbody2D>();
                    Vector3 dirVecR = player.transform.position - (transform.position + Vector3.right * 0.3f);
                    rigidR.AddForce(dirVecR.normalized * 4, ForceMode2D.Impulse);
                }
                {
                    GameObject bulletL = Instantiate(bulletObjectB, (transform.position + Vector3.left * 0.3f), transform.rotation);
                    Rigidbody2D rigidL = bulletL.GetComponent<Rigidbody2D>();
                    Vector3 dirVecL = player.transform.position - (transform.position + Vector3.left * 0.3f);
                    rigidL.AddForce(dirVecL.normalized * 4, ForceMode2D.Impulse);
                }
            }
        }
    }
        void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "BorderBullet")
        {
            Destroy(gameObject);
        }
        else if (collision.gameObject.tag == "PlayerBullet")
        {
            Bullet bullet = collision.gameObject.GetComponent<Bullet>();
            OnHit(bullet.dmg);
            Destroy(collision.gameObject);
        }
    }
}
#endif