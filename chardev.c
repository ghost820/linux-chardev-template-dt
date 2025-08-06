#include "chardev.h"
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/of.h>
#include <linux/platform_device.h>

MODULE_AUTHOR("Michal Miladowski <michal.miladowski@gmail.com>");
MODULE_DESCRIPTION("Character Device Driver Template");
MODULE_LICENSE("GPL");

static const struct of_device_id chardev_of_match[] = {
	{ .compatible = "chardev", .data = NULL },
	{}
};
MODULE_DEVICE_TABLE(of, chardev_of_match);

static int chardev_probe(struct platform_device *pdev)
{
	struct chardev_platform_data *pdata = NULL;
	struct device *dev = &pdev->dev;
	int ret;
	unsigned long data = 0;

	if (dev->of_node) {
		const struct of_device_id *id;

		id = of_match_device(of_match_ptr(chardev_of_match), dev);
		if (!id)
			return -ENODEV;

		pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
		if (!pdata)
			return -ENOMEM;

		data = (unsigned long)id->data;

		ret = of_property_read_string(dev->of_node, "ghost,someprop", &pdata->someprop);
		if (ret) {
			dev_err(dev, "Missing dt property ghost,someprop\n");
			return ret;
		}
	} else {
		if (!pdev->id_entry)
			return -EINVAL;

		data = pdev->id_entry->driver_data;
		pdata = dev_get_platdata(dev);
	}

	if (!pdata) {
		dev_err(dev, "No platform data\n");
		return -EINVAL;
	}

	if (!data) {
		dev_err(dev, "No driver data\n");
		return -EINVAL;
	}

    return 0;
}

static void chardev_remove(struct platform_device *pdev)
{
}

static const struct platform_device_id chardev_id[] = {
	{ .name = "chardev", .driver_data = 0 },
	{}
};
MODULE_DEVICE_TABLE(platform, chardev_id);

static struct platform_driver chardev_driver = {
	.driver	= {
		.name = "chardev",
		.of_match_table = of_match_ptr(chardev_of_match),
	},
	.probe = chardev_probe,
	.remove = chardev_remove,
	.id_table = chardev_id,
};
module_platform_driver(chardev_driver);
