# Differences between NodeGLUT and FreeGLUT

- glutInitErrorFunc :

```
Before:
glutInitErrorFunc(void (*callback) (const char* fmt, va_list ap))

After:
glutInitErrorFunc((message: String) => void)
```

- glutInitWarningFunc :

```
Before:
glutInitWarningFunc(void (*callback) (const char* fmt, va_list ap))

After:
glutInitWarningFunc((message: String) => void)
```

- glutGetProcAddress : Returns a raw C pointer (External Value)
